#pragma once

#include "Module.h"
#include "interfaces/IRemoteInvocation.h"

namespace WPEFramework {
namespace Exchange {

    struct IRemoteLinker : virtual public Core::IUnknown {

        enum { ID = ID_REMOTELINKER };

        virtual uint32_t Connect(const string& remoteAddress, const uint32_t interface, const uint32_t exchangeId) = 0;
        virtual uint32_t Disconnect() = 0;
    };
}
}
