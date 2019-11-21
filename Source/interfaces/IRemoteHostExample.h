#pragma once

#include "Module.h"

namespace WPEFramework {
namespace Exchange {

    struct IRemoteHostExample : virtual public Core::IUnknown {

        enum { ID = ID_REMOTEHOSTEXAMPLE };

        virtual ~IRemoteHostExample() {}

        virtual uint32_t Initialize(PluginHost::IShell* service) = 0;
        virtual uint32_t Greet(const string& name, string& response /* @out */) = 0;

    };
}
}
