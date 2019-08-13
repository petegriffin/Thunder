#ifndef __INOSINFO_H
#define __INOSINFO_H

#include "Module.h"

namespace WPEFramework {
namespace Exchange {

    // This interface is used for execution of functions in  NOSInfo Plugin

    struct INOSInfo : virtual public Core::IUnknown {
        enum { ID = 0x00000102 };

        virtual ~INOSInfo() {}
        virtual uint32_t Configure(PluginHost::IShell* service) = 0;
        virtual uint32_t Echo(string) = 0; //Sample function for testing ExternalAccess
    };
}
}

#endif // __INOSINFO_H
