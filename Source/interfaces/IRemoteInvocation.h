#pragma once

#include "Module.h"

namespace WPEFramework {
namespace Exchange {

    struct IRemoteInvocation : virtual public Core::IUnknown {

        enum { ID = ID_REMOTEINVOCATION };

        virtual ~IRemoteInvocation() {}
        struct ProgramParams {
            string callsign;
            string locator;
            string className;
            uint32_t interface;
            uint32_t logging;
            uint32_t id;
            uint32_t version;
            uint32_t threads;
        };

        virtual void Start(const string callingDevice, const ProgramParams& params) = 0;
    };
}
}