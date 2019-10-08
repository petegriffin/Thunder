#include "Channel.h"

namespace WPEFramework {

namespace JSONRPC {

    /* static */ FactoryImpl& FactoryImpl::Instance()
    {
        static FactoryImpl& _singleton = Core::SingletonType<FactoryImpl>::Instance();

        return (_singleton);
    }

    uint64_t FactoryImpl::WatchDog::Timed(const uint64_t /* scheduledTime */) {
       return (_client->Timed());
    }

    template <typename ACTUALSTREAM>
    class ChannelProxy : public Core::ProxyObject<ACTUALSTREAM> {
    private:
        ChannelProxy(const ChannelProxy&) = delete;
        ChannelProxy& operator=(const ChannelProxy&) = delete;
        ChannelProxy() = delete;

        ChannelProxy(const Core::NodeId& remoteNode, const string& callsign)
            : Core::ProxyObject<ACTUALSTREAM>(remoteNode, callsign)
        {
        }

        class Administrator {
        private:
            Administrator(const Administrator&) = delete;
            Administrator& operator=(const Administrator&) = delete;

            typedef std::map<const string, ACTUALSTREAM*> CallsignMap;

            static Administrator& Instance()
            {
                static Administrator& _instance = Core::SingletonType<Administrator>::Instance();
                return (_instance);
            }

        public:
            Administrator()
                : _adminLock()
                , _callsignMap()
            {
            }
            ~Administrator()
            {
            }

        public:
            static Core::ProxyType<ACTUALSTREAM> Instance(const Core::NodeId& remoteNode, const string& callsign)
            {
                return (Instance().InstanceImpl(remoteNode, callsign));
            }
            static uint32_t Release(ChannelProxy* object)
            {
                return (Instance().ReleaseImpl(object));
            }

        private:
            Core::ProxyType<ACTUALSTREAM> InstanceImpl(const Core::NodeId& remoteNode, const string& callsign)
            {
                Core::ProxyType<ACTUALSTREAM> result;

                _adminLock.Lock();

                string searchLine = remoteNode.HostName() + '@' + callsign;

                typename CallsignMap::iterator index(_callsignMap.find(searchLine));
                if (index != _callsignMap.end()) {
                    result = Core::ProxyType<ACTUALSTREAM>(*(index->second));
                } else {
                    ChannelProxy* entry = new (0) ChannelProxy(remoteNode, callsign);
                    _callsignMap[searchLine] = entry;
                    result = Core::ProxyType<ACTUALSTREAM>(*entry);
                }
                _adminLock.Unlock();

                ASSERT(result.IsValid() == true);

                if (result.IsValid() == true) {
                    static_cast<ChannelProxy&>(*result).Open(100);
                }

                return (result);
            }
            uint32_t ReleaseImpl(ChannelProxy* object)
            {
                _adminLock.Lock();

                uint32_t result = object->ActualRelease();

                if (result == Core::ERROR_DESTRUCTION_SUCCEEDED) {
                    // Oke remove the entry from the MAP.

                    typename CallsignMap::iterator index(_callsignMap.begin());

                    while ((index != _callsignMap.end()) && (&(*object) == index->second)) {
                        index++;
                    }

                    if (index != _callsignMap.end()) {
                        _callsignMap.erase(index);
                    }
                }

                _adminLock.Unlock();

                return (Core::ERROR_DESTRUCTION_SUCCEEDED);
            }

        private:
            Core::CriticalSection _adminLock;
            CallsignMap _callsignMap;
        };

    public:
        ~ChannelProxy()
        {
            // Guess we need to close
            ACTUALSTREAM::Close();
        }

        static Core::ProxyType<ACTUALSTREAM> Instance(const Core::NodeId& remoteNode, const string& callsign)
        {
            return (Administrator::Instance(remoteNode, callsign));
        }

    public:
        virtual uint32_t Release() const override
        {
            return (Administrator::Release(const_cast<ChannelProxy*>(this)));
        }

    private:
        uint32_t ActualRelease() const
        {
            return (Core::ProxyObject<ACTUALSTREAM>::Release());
        }
        bool Open(const uint32_t waitTime)
        {
            return (ACTUALSTREAM::Open(waitTime));
        }

    private:
        Core::CriticalSection _adminLock;
    };

    /* static */ Core::ProxyType<ChannelJSON> ChannelJSON::Instance(const Core::NodeId& remoteNode, const string& callsign)
    {
        return (ChannelProxy<ChannelJSON>::Instance(remoteNode, callsign));
    }

    void ChannelJSON::StateChange()
    {
        _adminLock.Lock();
        typename std::list<IClient*>::iterator index(_observers.begin());
        while (index != _observers.end()) {
            if (_channel.IsOpen() == true) {
                (*index)->Opened();
            } else {
                (*index)->Closed();
            }
            index++;
        }
        _adminLock.Unlock();
    }
    uint32_t ChannelJSON::Inbound(const Core::ProxyType<Core::JSONRPC::Message>& inbound)
    {
        uint32_t result = Core::ERROR_UNAVAILABLE;
        _adminLock.Lock();
        typename std::list<IClient*>::iterator index(_observers.begin());
        while ((result != Core::ERROR_NONE) && (index != _observers.end())) {
            result = (*index)->Inbound(inbound);
            index++;
        }
        _adminLock.Unlock();

        return (result);
    }
}
}
