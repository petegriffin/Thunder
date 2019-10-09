#ifndef __STREAMJSON__
#define __STREAMJSON__

#include "JSON.h"
#include "Module.h"
#include "Portability.h"
#include "StreamText.h"

namespace WPEFramework {
namespace Core {

    struct JSONType {
        template <typename T>
        struct HasMessagePackAvailable {
            template <typename U, void (U::*)(const std::string&)>
            struct SFINAE {
            };
            template <typename U>
            static uint8_t Test(SFINAE<U, &U::OnMessagePackAvailable>*);
            template <typename U>
            static uint32_t Test(...);
            static const bool Has = sizeof(Test<T>(0)) == sizeof(uint8_t);
        };
        static void ToMessagePack(const string& parameters, Core::ProxyType<Core::JSONRPC::Message>& message, std::true_type)
        {
            string values = parameters;
            if (values.empty() != true) {
                message->Parameters = values;
            }
            return;
        }
        static void ToMessagePack(const Core::JSON::IMessagePack& parameters, Core::ProxyType<Core::JSONRPC::Message>& message, std::true_type)
        {
            std::vector<uint8_t> values;
            parameters.ToBuffer(values);
            if (values.empty() != true) {
                //message->Parameters = values;
            }
            return;
        }
        template <typename RESPONSE>
        static void ToMessagePack(const RESPONSE& response, Core::ProxyType<Core::JSONRPC::Message>& message, std::false_type)
        {
        }
        template <typename RESPONSE>
        static void FromMessagePack(RESPONSE& response, const Core::JSONRPC::Message& message, std::true_type)
        {
            std::vector<uint8_t> values;
            //response.FromBuffer(message);
            return;
        }
        template <typename PARAMETERS>
        static void FromMessagePack(PARAMETERS& parameters, const Core::JSONRPC::Message& message, std::false_type)
        {
        }
        template <typename INTERFACE>
        static uint16_t SerializeMessagePack(INTERFACE message, uint8_t* stream, const uint16_t length, uint16_t offset, std::true_type) {
            return message->Serialize(stream, length, offset);
        }
        template <typename INTERFACE>
        static uint16_t SerializeMessagePack(INTERFACE message, uint8_t* stream, const uint16_t length, uint16_t offset, std::false_type) {
            return 0;
        }
        template <typename INTERFACE>
        static uint16_t DeserializeMessagePack(INTERFACE& message, const uint8_t* stream, const uint16_t length, uint16_t offset, std::true_type) {
            return message.Deserialize(stream, length, offset);
        }
        template <typename INTERFACE>
        static uint16_t DeserializeMessagePack(INTERFACE& message, const uint8_t* stream, const uint16_t length, uint16_t offset, std::false_type) {
            return 0;
        }
        template <typename T>
        struct HasElementAvailable {
            template <typename U, void (U::*)(const std::string&)>
            struct SFINAE {
            };
            template <typename U>
            static uint8_t Test(SFINAE<U, &U::OnElementAvailable>*);
            template <typename U>
            static uint32_t Test(...);
            static const bool Has = sizeof(Test<T>(0)) == sizeof(uint8_t);
        };
        static void ToElement(const string& parameters, Core::ProxyType<Core::JSONRPC::Message>& message, std::true_type)
        {
            string values = parameters;
            if (values.empty() != true) {
                message->Parameters = values;
            }
            return;
        }
        static void ToElement(const Core::JSON::IElement& parameters, Core::ProxyType<Core::JSONRPC::Message>& message, std::true_type)
        {
            string values;
            parameters.ToString(values);
            if (values.empty() != true) {
                message->Parameters = values;
            }
            return;
        }
        template <typename RESPONSE>
        static void ToElement(const RESPONSE& response, Core::ProxyType<Core::JSONRPC::Message>& message, std::false_type)
        {
        }
        template <typename RESPONSE>
        static void FromElement(RESPONSE& response, const Core::JSONRPC::Message& message, std::true_type)
        {
            std::vector<uint8_t> values;
            //response.FromString(message);
            return;
        }
        template <typename PARAMETERS>
        static void FromElement(PARAMETERS& parameters, const Core::JSONRPC::Message& message, std::false_type)
        {
        }
        template <typename INTERFACE>
        static uint16_t SerializeElement(INTERFACE element, uint8_t* stream, const uint16_t length, uint16_t offset, std::true_type) {
            return element->Serialize(reinterpret_cast<char*>(stream), length, offset);
        }
        template <typename INTERFACE>
        static uint16_t SerializeElement(INTERFACE element, uint8_t* stream, const uint16_t length, uint16_t offset, std::false_type) {
            return 0;
        }
        template <typename INTERFACE>
        static uint16_t DeserializeElement(INTERFACE& element, const uint8_t* stream, const uint16_t length, uint16_t offset, std::true_type) {
            return element->Deserialize(reinterpret_cast<const char*>(stream), length, offset);
        }
        template <typename INTERFACE>
        static uint16_t DeserializeElement(INTERFACE& element, const uint8_t* stream, const uint16_t length, uint16_t offset, std::false_type) {
            return 0;
        }
    };

    template <typename INTERFACE, typename SOURCE, typename ALLOCATOR>
    class StreamJSONType {
    private:
        typedef StreamJSONType<INTERFACE, SOURCE, ALLOCATOR> ParentClass;

        class SerializerImpl {
        public:
            SerializerImpl() = delete;
            SerializerImpl(const SerializerImpl&) = delete;
            SerializerImpl& operator=(const SerializerImpl&) = delete;

            SerializerImpl(ParentClass& parent, const uint8_t slotSize)
                : _parent(parent)
                , _adminLock()
                , _sendQueue(slotSize)
                , _offset(0)
            {
            }
            ~SerializerImpl()
            {
            }

        public:
            inline bool IsIdle() const
            {
                return (_sendQueue.Count() == 0);
            }
            bool Submit(const ProxyType<INTERFACE>& entry)
            {
                _adminLock.Lock();

                _sendQueue.Add(const_cast<ProxyType<INTERFACE>&>(entry));

                bool trigger = (_sendQueue.Count() == 1);

                _adminLock.Unlock();

                return (trigger);
            }
            inline uint16_t Serialize(uint8_t* stream, const uint16_t length) const
            {
                uint16_t loaded = 0;

                _adminLock.Lock();

                if (_sendQueue.Count() > 0) {
                    if (Core::JSONType::HasMessagePackAvailable<INTERFACE>::Has == true) {
                        loaded = Core::JSONType::SerializeMessagePack(_sendQueue[0], stream, length, _offset, std::integral_constant<bool, Core::JSONType::HasMessagePackAvailable<INTERFACE>::Has>());
                    } else if (Core::JSONType::HasElementAvailable<INTERFACE>::Has == true) {
                        loaded = Core::JSONType::SerializeElement(_sendQueue[0], stream, length, _offset, std::integral_constant<bool, Core::JSONType::HasElementAvailable<INTERFACE>::Has>());
                    }
 
                    if ((_offset == 0) || (loaded != length)) {
                        Core::ProxyType<INTERFACE> current = _sendQueue[0];
                        _parent.Send(current);

                        _sendQueue.Remove(0);
                        _offset = 0;
                    }
                }

                _adminLock.Unlock();

                return (loaded);
            }

        private:
            ParentClass& _parent;
            mutable Core::CriticalSection _adminLock;
            mutable Core::ProxyList<INTERFACE> _sendQueue;
            mutable uint16_t _offset;
        };
        template <typename OBJECTALLOCATOR>
        class DeserializerImpl {
        public:
            DeserializerImpl() = delete;
            DeserializerImpl(const DeserializerImpl<OBJECTALLOCATOR>&) = delete;
            DeserializerImpl<OBJECTALLOCATOR>& operator=(const DeserializerImpl<OBJECTALLOCATOR>&) = delete;

            DeserializerImpl(ParentClass& parent, const uint8_t slotSize)
                : _parent(parent)
                , _factory(slotSize)
                , _current()
                , _offset(0)
            {
            }
            DeserializerImpl(ParentClass& parent, OBJECTALLOCATOR allocator)
                : _parent(parent)
                , _factory(allocator)
                , _current()
                , _offset(0)
            {
			}
            ~DeserializerImpl()
            {
            }

        public:
            inline bool IsIdle() const
            {
                return (_current.IsValid() == false);
            }
            inline uint16_t Deserialize(const uint8_t stream[], const uint16_t length)
            {
                uint16_t loaded = 0;

                if (_current.IsValid() == false) {
                    _current = Core::ProxyType<INTERFACE>(_factory.Element(EMPTY_STRING));
                    _offset = 0;
                }
                if (_current.IsValid() == true) {
                    if (Core::JSONType::HasMessagePackAvailable<INTERFACE>::Has == true) {
                        loaded = Core::JSONType::DeserializeMessagePack(_current, stream, length, _offset, std::integral_constant<bool, Core::JSONType::HasMessagePackAvailable<INTERFACE>::Has>());
                    } else if (Core::JSONType::HasElementAvailable<INTERFACE>::Has == true) {
                        loaded = Core::JSONType::DeserializeElement(_current, stream, length, _offset, std::integral_constant<bool, Core::JSONType::HasElementAvailable<INTERFACE>::Has>());
                    }
                    if ((_offset == 0) || (loaded != length)) {
                        _parent.Received(_current);
                        _current.Release();
                    }
                }

                return (loaded);
            }

        private:
            ParentClass& _parent;
            ALLOCATOR _factory;
            Core::ProxyType<INTERFACE> _current;
            uint16_t _offset;
        };

        template <typename PARENTCLASS, typename ACTUALSOURCE>
        class HandlerType : public ACTUALSOURCE {
        public:
            HandlerType() = delete;
            HandlerType(const HandlerType<PARENTCLASS, ACTUALSOURCE>&) = delete;
            HandlerType<PARENTCLASS, ACTUALSOURCE>& operator=(const HandlerType<PARENTCLASS, ACTUALSOURCE>&) = delete;

            HandlerType(PARENTCLASS& parent)
                : ACTUALSOURCE()
                , _parent(parent)
            {
            }
            template <typename... Args>
            HandlerType(PARENTCLASS& parent, Args... args)
                : ACTUALSOURCE(args...)
                , _parent(parent)
            {
            }
            ~HandlerType()
            {
            }

        public:
            // Methods to extract and insert data into the socket buffers
            virtual uint16_t SendData(uint8_t* dataFrame, const uint16_t maxSendSize)
            {
                return (_parent.SendData(dataFrame, maxSendSize));
            }

            virtual uint16_t ReceiveData(uint8_t* dataFrame, const uint16_t receivedSize)
            {
                return (_parent.ReceiveData(dataFrame, receivedSize));
            }

            // Signal a state change, Opened, Closed or Accepted
            virtual void StateChange()
            {
                _parent.StateChange();
            }
            virtual bool IsIdle() const
            {
                return (_parent.IsIdle());
            }

        private:
            PARENTCLASS& _parent;
        };

        typedef StreamTextType<SOURCE, ALLOCATOR> BaseClass;

    public:
        StreamJSONType(const StreamJSONType<INTERFACE, SOURCE, ALLOCATOR>&) = delete;
        StreamJSONType<INTERFACE, SOURCE, ALLOCATOR>& operator=(const StreamJSONType<INTERFACE, SOURCE, ALLOCATOR>&) = delete;

#ifdef __WIN32__
#pragma warning(disable : 4355)
#endif
        template <typename... Args>
        StreamJSONType(uint8_t slotSize, ALLOCATOR& allocator, Args... args)
            : _channel(*this, args...)
            , _serializer(*this, slotSize)
            , _deserializer(*this, allocator)
        {
        }

        template <typename... Args>
        StreamJSONType(uint8_t slotSize, Args... args)
            : _channel(*this, args...)
            , _serializer(*this, slotSize)
            , _deserializer(*this, slotSize)
        {
        }
#ifdef __WIN32__
#pragma warning(default : 4355)
#endif

        virtual ~StreamJSONType()
        {
            _channel.Close(Core::infinite);
        }

    public:
        inline SOURCE& Link()
        {
            return (_channel);
        }
        virtual void Received(ProxyType<INTERFACE>& element) = 0;
        virtual void Send(ProxyType<INTERFACE>& element) = 0;
        virtual void StateChange() = 0;

        inline void Submit(const ProxyType<INTERFACE>& element)
        {
            if (_channel.IsOpen() == true) {
                _serializer.Submit(element);
                _channel.Trigger();
            }
        }
        inline uint32_t Open(const uint32_t waitTime)
        {
            return (_channel.Open(waitTime));
        }
        inline uint32_t Close(const uint32_t waitTime)
        {
            return (_channel.Close(waitTime));
        }
        inline bool IsOpen() const
        {
            return (_channel.IsOpen());
        }
        inline bool IsClosed() const
        {
            return (_channel.IsClosed());
        }
        inline bool IsSuspended() const
        {
            return (_channel.IsSuspended());
        }

    private:
        virtual bool IsIdle() const
        {
            return ((_serializer.IsIdle() == true) && (_deserializer.IsIdle() == true));
        }
        uint16_t SendData(uint8_t* dataFrame, const uint16_t maxSendSize)
        {
            return (_serializer.Serialize(dataFrame, maxSendSize));
        }
        uint16_t ReceiveData(uint8_t* dataFrame, const uint16_t receivedSize)
        {
            uint16_t handled = 0;

            do {
                handled += _deserializer.Deserialize(&dataFrame[handled], (receivedSize - handled));

                // The dataframe can hold more items....
            } while (handled < receivedSize);

            return (handled);
        }

    private:
        HandlerType<ParentClass, SOURCE> _channel;
        SerializerImpl _serializer;
        DeserializerImpl<ALLOCATOR> _deserializer;
    };
}
} // namespace Core

#endif // __STREAMJSON__
