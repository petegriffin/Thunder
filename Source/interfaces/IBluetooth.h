#pragma once

// @stubgen:skip

#include "Module.h"

namespace WPEFramework {

namespace Exchange {

    // This interface gives direct access to a Bluetooth server instance, running as a plugin in the framework.
    struct IBluetooth : virtual public Core::IUnknown {

        enum { ID = ID_BLUETOOTH };

        virtual ~IBluetooth() {}

        struct IDevice : virtual public Core::IUnknown {

            enum { ID = ID_BLUETOOTH_DEVICE };

            struct IIterator : virtual public Core::IUnknown {

                enum { ID = ID_BLUETOOTH_DEVICE_ITERATOR };

                virtual ~IIterator() {}

                virtual void Reset() = 0;
                virtual bool IsValid() const = 0;
                virtual bool Next() = 0;
                virtual IDevice* Current() = 0;
            };

            virtual ~IDevice() {}

            virtual string Address() const = 0;
            virtual string Name() const = 0;
            virtual bool IsDiscovered() const = 0;
            virtual bool IsPaired() const = 0;
            virtual bool IsConnected() const = 0;
            virtual uint32_t Pair() = 0;
            virtual uint32_t Unpair() = 0;
            virtual uint32_t Connect() = 0;
            virtual uint32_t Disconnect(const uint16_t reason) = 0;

            virtual bool Reset(string, bool = false) = 0;

            enum BluetoothEvents
            {
                ePairingStarted,
                ePairingFailed,
                ePairingSuccess,
                ePairingTimeout,
                MAX_EVENT_ID
            };

            struct INotification : virtual public IUnknown {
                //TODO Give an ID
                enum {ID = 0x0000010a};

                virtual ~INotification()
                {
                }

                //Used to get events from the Bluetooth interface.
                virtual void GetBluetoothEvents(const BluetoothEvents) = 0;
            };

            virtual void RegisterBluetoothEvents(IBluetooth::INotification* sink) = 0;
            virtual void UnregisterBluetoothEvents(IBluetooth::INotification* sink) = 0;

        };

        struct INotification : virtual public Core::IUnknown {

            enum { ID = ID_BLUETOOTH_NOTIFICATION };

            virtual ~INotification() {}

            virtual void Update(IDevice* device);
        };

        virtual bool IsScanning() const = 0;
        virtual uint32_t Register(INotification* notification) = 0;
        virtual uint32_t Unregister(INotification* notification) = 0;

        virtual bool Scan(const bool enable) = 0;
        virtual IDevice* Device(const string&) = 0;
        virtual IDevice::IIterator* Devices() = 0;
    };
}
}
