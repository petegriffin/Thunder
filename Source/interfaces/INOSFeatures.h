#ifndef __INOSFEATURES_H
#define __INOSFEATURES_H

#include "Module.h"

namespace WPEFramework {
namespace Exchange {

    // This interface is used for execution of functions in  NOSPlugin

    struct INOSFeatures : virtual public Core::IUnknown {
        enum { ID = 0x00000101 };

        virtual ~INOSFeatures() {}
        virtual uint32_t Configure(PluginHost::IShell* service) = 0;
        virtual uint32_t Echo(string) = 0;
        virtual bool DoFactoryReset() = 0;
        virtual void SendEvent(uint32_t ) = 0;
        virtual void BluetoothForcePairingStarted() = 0;
        virtual void PowerStateChanged(string powerstate) = 0;
    };
}
}

#endif // __INOSFEATURES_H