#include "Module.h"

#include "gstreamerclient.h"
#include "compositorclient/Client.h"
#include "interfaces/IComposition.h"

#include <gst/gst.h>
#include <gst/app/gstappsrc.h>
#include <gst/video/videooverlay.h>

using namespace WPEFramework;
using SafeCriticalSection = Core::SafeSyncType<Core::CriticalSection>;

// TODO: where best to init gst?
// TODO: gst should already have been inited (we don't create the pipeline, for example)
bool g_gstInited = false;

static Core::CriticalSection g_adminLock;

struct GstPlayerSink {
private:
    GstPlayerSink(const GstPlayerSink&) = delete;
    GstPlayerSink& operator= (const GstPlayerSink&) = delete;

public:
    GstPlayerSink(GstElement * pipeline)
            : _pipeline(pipeline)
            , _audioDecodeBin(nullptr)
            , _videoDecodeBin(nullptr)
            , _audioSink(nullptr)
            , _videoSink(nullptr)
            , _videoDec(nullptr)
            , _audioCallbacks(nullptr)
            , _videoCallbacks(nullptr)
            , _glImage(nullptr)
    {
    }

public:
    bool ConfigureAudioSink(GstElement * srcElement, GstPad *srcPad, GstreamerClientCallbacks *callbacks) {
        TRACE_L1("Configure audio sink");

        if (_audioDecodeBin) {
            TRACE_L1("Audio Sink is already configured");
            return false;
        }

        // Setup audio decodebin
        _audioDecodeBin = gst_element_factory_make ("decodebin", "audio_decode");
        if (!_audioDecodeBin)
            return false;

        g_signal_connect(_audioDecodeBin, "pad-added", G_CALLBACK(OnAudioPad), this);
        g_object_set(_audioDecodeBin, "caps", gst_caps_from_string("audio/x-raw;"), nullptr);

        // Create an audio sink
        _audioSink = gst_element_factory_make ("autoaudiosink", "audio-sink");
        if (!_audioSink)
            return false;

        gst_bin_add_many (GST_BIN (_pipeline), _audioDecodeBin, _audioSink, nullptr);

        if (srcPad != nullptr) {
           // Link via pad
           GstPad *pSinkPad = gst_element_get_static_pad(_audioDecodeBin, "sink");
           gst_pad_link (srcPad, pSinkPad);
           gst_object_unref(pSinkPad);
        } else {
           // Link elements
           gst_element_link(srcElement, _audioDecodeBin);
        }

        return true;
    }

    bool ConfigureVideoSink(GstElement * srcElement, GstPad *srcPad, GstreamerClientCallbacks *callbacks) {

        // Initialize Surface
        if (!_surface)
            _surface = WPEFramework::Compositor::IDisplay::Instance("AmazonPlayer")->Create("AmazonVideo", 0, 0);

        // Setup video decodebin
        _videoDecodeBin = gst_element_factory_make ("decodebin", "video_decode");
        if(!_videoDecodeBin)
            return false;

        g_signal_connect(_videoDecodeBin, "pad-added", G_CALLBACK(OnVideoPad), this);
        g_object_set(_videoDecodeBin, "caps", gst_caps_from_string("video/x-raw;"), nullptr);

        // Create video sink
        _videoSink       = gst_element_factory_make ("videoscale", "video_scale");
        if (!_videoSink) {
            TRACE_L1("Failed to create video-scaling bin!");
            return false;
        }

        _glImage = gst_element_factory_make ("glimagesink", "glimagesink0");
        if (_glImage == nullptr) {
            TRACE_L1("Failed to create glimagesink!");
            return false;
        }

        gst_bin_add_many (GST_BIN (_pipeline), _videoDecodeBin, _videoSink, _glImage, nullptr);

        if (srcPad != nullptr) {
           // Link via pad
           GstPad *pSinkPad = gst_element_get_static_pad(_videoDecodeBin, "sink");
           gst_pad_link (srcPad, pSinkPad);
           gst_object_unref(pSinkPad);
        } else {
           // Link elements
           gst_element_link(srcElement, _videoDecodeBin);
        }

        if (gst_element_link_filtered(_videoSink, _glImage, gst_caps_from_string("video/x-raw,width=1280,height=720")) == false) {
            TRACE_L1("Failed to link video scaling with image sink");
            return false;
        }
        
        GstBus *bus = gst_pipeline_get_bus (GST_PIPELINE (_pipeline));
        gst_bus_set_sync_handler (bus, (GstBusSyncHandler) createWindow, this, NULL);
        gst_object_unref(bus);

        return true;
    }

    void DestructSink() {

        if (_videoDecodeBin) {
            g_signal_handlers_disconnect_by_func(_videoDecodeBin, reinterpret_cast<gpointer>(OnVideoPad), this);
            g_signal_handlers_disconnect_by_func(_videoDecodeBin, reinterpret_cast<gpointer>(OnVideoElementAdded), this);
            g_signal_handlers_disconnect_by_func(_videoDecodeBin, reinterpret_cast<gpointer>(OnVideoElementRemoved), this);
        }

        if (_audioDecodeBin) {
            g_signal_handlers_disconnect_by_func(_audioDecodeBin, reinterpret_cast<gpointer>(OnAudioPad), this);
            g_signal_handlers_disconnect_by_func(_audioDecodeBin, reinterpret_cast<gpointer>(OnAudioElementAdded), this);
            g_signal_handlers_disconnect_by_func(_audioDecodeBin, reinterpret_cast<gpointer>(OnAudioElementRemoved), this);
        }
        
        // TODO: delete surface?
    }

/*
    void Deinitialise() {
        if (_surface) {
            // Delete surface
            _surface->Release();
            _surface = nullptr;
        }
    }
*/

    uint64_t FramesRendered() {
        // TODO
        guint64 decodedFrames = 0;
        if (_videoSink) {
            g_object_get(_videoSink, "frames-rendered", &decodedFrames, nullptr);
        }
        TRACE_L1("frames decoded: %llu",  decodedFrames);

        return decodedFrames;
    }

    uint64_t FramesDropped() {
        // TODO
        guint64 droppedFrames = 0;

        if (_videoSink) {
            g_object_get(_videoSink, "frames-dropped", &droppedFrames, nullptr);
        }
        TRACE_L1("frames dropped: %llu",  droppedFrames);

        return droppedFrames;
    }

    bool GetResolution(uint32_t& width, uint32_t& height)
    {
        // TODO
       gint sourceHeight = 0;
       gint sourceWidth = 0;

       if (!_videoDec) {
          TRACE_L1("No video decoder when querying resolution");
          return false;
       }

       g_object_get(_videoDec, "video_height", &sourceHeight, NULL);
       g_object_get(_videoDec, "video_width", &sourceWidth, NULL);

       width = static_cast<uint32_t>(sourceWidth);
       height = static_cast<uint32_t>(sourceHeight);
       return true;
    }

    GstClockTime GetCurrentPosition()
    {
       gint64 currentPts = GST_CLOCK_TIME_NONE;
       GstQuery* query = gst_query_new_position(GST_FORMAT_TIME);
       if (gst_element_query(_pipeline, query))
          gst_query_parse_position(query, 0, &currentPts);

       gst_query_unref(query);    

       return static_cast<GstClockTime>(currentPts);
    }
    
    bool MoveVideoRectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
       if (_videoSink == nullptr) {
          TRACE_L1("No video sink to move rectangle for");
          return false;
       }

       char rectString[64];
       sprintf(rectString,"%d,%d,%d,%d", x, y, width, height);
       g_object_set(_videoSink, "rectangle", rectString, nullptr);
      
       return true;
    }

    bool SetVolume(double volume)
    {
       g_object_set(G_OBJECT(_audioSink), "volume", volume, NULL);

       return true;
    }
    
private:

    static GstBusSyncReply createWindow (GstBus * bus, GstMessage * message, gpointer user_data) {
        // ignore anything but 'prepare-window-handle' element messages
        if (!gst_is_video_overlay_prepare_window_handle_message(message))
            return GST_BUS_PASS;

        GstPlayerSink *self = (GstPlayerSink*)(user_data);

        GstVideoOverlay *overlay = GST_VIDEO_OVERLAY (GST_MESSAGE_SRC (message));
        gst_video_overlay_set_window_handle (overlay, (guintptr)self->_surface->Native());

        return GST_BUS_DROP;

    }
    static void OnVideoPad (GstElement *decodebin2, GstPad *pad, gpointer user_data) {

        GstPlayerSink *self = (GstPlayerSink*)(user_data);

        GstCaps *caps;
        GstStructure *structure;
        const gchar *name;

        caps = gst_pad_query_caps(pad,nullptr);
        structure = gst_caps_get_structure(caps,0);
        name = gst_structure_get_name(structure);

        if (g_strrstr(name, "video/x-"))
        {

            //self->_surface->setLayer(-1);

            if (gst_element_link(self->_videoDecodeBin, self->_videoSink) == FALSE) {
                TRACE_L1("Could not make link video sink to bin");
            }
        }
        gst_caps_unref(caps);
    }

    static void OnAudioPad (GstElement *decodebin2, GstPad *pad, gpointer user_data) {
        GstPlayerSink *self = (GstPlayerSink*)(user_data);

        GstCaps *caps;
        GstStructure *structure;
        const gchar *name;

        caps = gst_pad_query_caps(pad,nullptr);
        structure = gst_caps_get_structure(caps,0);
        name = gst_structure_get_name(structure);

        if (g_strrstr(name, "audio/x-"))
        {
            if (gst_element_link(self->_audioDecodeBin, self->_audioSink) == FALSE) {
                printf("Could not make link audio sink to bin\n");
            }
        }
        gst_caps_unref(caps);
    }
    
// Begin copy paste from nexus
// TODO: use rpi names, and: is this the same as earlier onvideopad/onaudiopad functions?    
    static void OnVideoElementAdded (GstBin *decodebin2, GstElement* element, gpointer user_data) {

        GstPlayerSink *self = (GstPlayerSink*)(user_data);

        if (g_strrstr(GST_ELEMENT_NAME(element), "brcmvideodecoder")) {
            self->_videoDec = element;

            if (self->_videoCallbacks) {

                g_signal_connect(element, "buffer-underflow-callback",
                                 G_CALLBACK(self->_videoCallbacks->buffer_underflow_callback),
                                 self->_videoCallbacks->user_data);
            }
        }
    }

    static void OnVideoElementRemoved (GstBin *decodebin2, GstElement* element, gpointer user_data) {

        GstPlayerSink *self = (GstPlayerSink*)(user_data);

        if (g_strrstr(GST_ELEMENT_NAME(element), "brcmvideodecoder")) {

            self->_videoDec = nullptr;
            if (self->_videoCallbacks) {
                g_signal_handlers_disconnect_by_func(element,
                                                     reinterpret_cast<gpointer>(self->_videoCallbacks->buffer_underflow_callback),
                                                     self->_videoCallbacks->user_data);
            }
        }
    }

    static void OnAudioElementAdded (GstBin *decodebin2, GstElement* element, gpointer user_data) {

        GstPlayerSink *self = (GstPlayerSink*)(user_data);

        if (!self->_audioCallbacks)
            return;

        if (g_strrstr(GST_ELEMENT_NAME(element), "brcmaudiodecoder"))
        {
            g_signal_connect(element, "buffer-underflow-callback",
                             G_CALLBACK(self->_audioCallbacks->buffer_underflow_callback), self->_videoCallbacks->user_data);
        }
    }

    static void OnAudioElementRemoved (GstBin *decodebin2, GstElement* element, gpointer user_data) {

        GstPlayerSink *self = (GstPlayerSink*)(user_data);

        if (!self->_audioCallbacks)
            return;

        if (g_strrstr(GST_ELEMENT_NAME(element), "brcmaudiodecoder"))
        {
            g_signal_handlers_disconnect_by_func(element,
                                                 reinterpret_cast<gpointer>(self->_audioCallbacks->buffer_underflow_callback), self->_videoCallbacks->user_data);
        }
    }
// end copy paste from nexus    

private:
    GstElement *_pipeline;
    GstElement *_audioDecodeBin;
    GstElement *_videoDecodeBin;
    GstElement *_audioSink;
    GstElement *_videoSink;
    GstElement *_videoDec;
    GstreamerClientCallbacks *_audioCallbacks;
    GstreamerClientCallbacks *_videoCallbacks;
    GstElement *_glImage;

    WPEFramework::Compositor::IDisplay::ISurface* _surface;
};

struct GstPlayer {
private:
    GstPlayer(const GstPlayer&) = delete;
    GstPlayer& operator= (const GstPlayer&) = delete;
    GstPlayer()
        : _sinks() {
    }

public:
    typedef std::map<GstElement*, GstPlayerSink*> SinkMap;

    static GstPlayer* Instance() {
        static GstPlayer *instance = new GstPlayer();

        return (instance);
    }

    void Add (GstElement* pipeline, GstPlayerSink* sink) {
        SinkMap::iterator index(_sinks.find(pipeline));

        if (index == _sinks.end()) {
            _sinks.insert(std::pair<GstElement*, GstPlayerSink*>(pipeline, sink));
        } else {
            TRACE_L1("Same pipeline created!");
        }
    }

    void Remove(GstElement* pipeline) {

        SinkMap::iterator index(_sinks.find(pipeline));

        if (index != _sinks.end()) {
            _sinks.erase(index);
        } else {
            TRACE_L1("Could not find a pipeline to remove");
        }
    }

    GstPlayerSink* Find(GstElement* pipeline) {

        GstPlayerSink* result = nullptr;
        SinkMap::iterator index(_sinks.find(pipeline));

        if (index != _sinks.end()) {
            result = index->second;
        }
        return result;
    }

private:
    SinkMap _sinks;
};

extern "C" {

#define TRACE_FUNC() {                                      \
    fprintf(stderr, ">> RPI %s \n", __PRETTY_FUNCTION__);   \
}

int gstreamer_client_sink_link (SinkType type, GstElement *pipeline, GstElement * srcElement, GstPad *srcPad, GstreamerClientCallbacks* callbacks)
{TRACE_FUNC();
    if (!g_gstInited) {
       gst_init (nullptr, nullptr);
       g_gstInited = true;
    }

    SafeCriticalSection lock(g_adminLock);
    struct GstPlayer* instance = GstPlayer::Instance();
    int result = 0;

    GstPlayerSink *sink =  instance->Find(pipeline);
    if (!sink) {
        // create a new sink
        sink = new GstPlayerSink(pipeline);
        instance->Add(pipeline, sink);
    }

    switch (type) {
        case THUNDER_GSTREAMER_CLIENT_AUDIO:
            if (!sink->ConfigureAudioSink(srcElement, srcPad, callbacks)) {
                gstreamer_client_sink_unlink(type, pipeline);
                result = -1;
            }
            break;
        case THUNDER_GSTREAMER_CLIENT_VIDEO:
            if (!sink->ConfigureVideoSink(srcElement, srcPad, callbacks)) {
                gstreamer_client_sink_unlink(type, pipeline);
                result = -1;
            }
            break;
        case THUNDER_GSTREAMER_CLIENT_TEXT:
        default:
            result = -1;
            break;
    }

    fprintf(stderr, "<< gstreamer_client_sink_link\n");
    return result;
}

int gstreamer_client_sink_unlink (SinkType type, GstElement *pipeline)
{TRACE_FUNC();
    SafeCriticalSection lock(g_adminLock);
    struct GstPlayer* instance = GstPlayer::Instance();

    GstPlayerSink *sink =  instance->Find(pipeline);
    if (!sink)
        return -1;

    // Cleanup linked signals, pads etc.
    sink->DestructSink();

    // Remove from pipeline list
    instance->Remove(pipeline);

    // pipeline destruction will free allocated elements
    return 0;
}

unsigned long gtsreamer_client_sink_frames_rendered (GstElement *pipeline)
{TRACE_FUNC();
    SafeCriticalSection lock(g_adminLock);
    struct GstPlayer* instance = GstPlayer::Instance();
    GstPlayerSink *sink =  instance->Find(pipeline);

    if (!sink)
        return 0;

    return (sink->FramesRendered());
}

unsigned long gtsreamer_client_sink_frames_dropped (GstElement *pipeline)
{TRACE_FUNC();
    SafeCriticalSection lock(g_adminLock);
    struct GstPlayer* instance = GstPlayer::Instance();
    GstPlayerSink *sink =  instance->Find(pipeline);

    if (!sink)
        return 0;

    return (sink->FramesDropped());
}

int gstreamer_client_post_eos (GstElement * element)
{TRACE_FUNC();
    SafeCriticalSection lock(g_adminLock);
    gst_element_post_message(element, gst_message_new_eos(GST_OBJECT(element)));
    return 0;
}

int gstreamer_client_can_report_stale_pts ()
{TRACE_FUNC();
    return 0;
}

int gstreamer_client_set_volume(GstElement *pipeline, double volume)
{TRACE_FUNC();
   SafeCriticalSection lock(g_adminLock);
   GstPlayer* instance = GstPlayer::Instance();
   GstPlayerSink *sink =  instance->Find(pipeline);
   if (sink == nullptr) {
      TRACE_L1("Trying to set volume for unregistered pipeline");
      return 0;
   }
   bool success = sink->SetVolume(volume);
   return (success ? 1 : 0);
}

int gstreamer_client_get_resolution(GstElement *pipeline, uint32_t * width, uint32_t * height)
{TRACE_FUNC();
   SafeCriticalSection lock(g_adminLock);
   GstPlayer* instance = GstPlayer::Instance();
   GstPlayerSink *sink =  instance->Find(pipeline);
   if (sink == nullptr) {
      TRACE_L1("Trying to get resolution for unregistered pipeline");
      return 0;
   }
   bool success = sink->GetResolution(*width, *height);
   return (success ? 1 : 0);
}

GstClockTime gstreamer_client_get_current_position(GstElement *pipeline)
{TRACE_FUNC();
   SafeCriticalSection lock(g_adminLock);
   GstPlayer* instance = GstPlayer::Instance();
   GstPlayerSink *sink =  instance->Find(pipeline);
   if (sink == nullptr) {
      TRACE_L1("Trying to get current position for unregistered pipeline");
      return 0;
   }
   return sink->GetCurrentPosition();

   // For other platforms, see:
   // https://github.com/Metrological/netflix/blob/1fb2cb81c75efd7c89f25f84aae52919c6d1fece/partner/dpi/gstreamer/PlaybackGroupNative.cpp#L1003-L1010
}

int gstreamer_client_move_video_rectangle(GstElement *pipeline, uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{TRACE_FUNC();
  SafeCriticalSection lock(g_adminLock);
  GstPlayer* instance = GstPlayer::Instance();
  GstPlayerSink *sink =  instance->Find(pipeline);
  if (sink == nullptr) {
      TRACE_L1("Trying to move video rectangle for unregistered pipeline");
      return 0;
  }
  
  bool success = sink->MoveVideoRectangle(x, y, width, height);
  return (success ? 1 : 0);
}

};

