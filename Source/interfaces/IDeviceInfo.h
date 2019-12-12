#pragma once

#include "Module.h"

namespace WPEFramework {
namespace Exchange {
    struct IDeviceInfo : virtual public Core::IUnknown {
        enum { ID = ID_DEVICEINFO };

        virtual const std::string FirmwareVersion() const = 0;
        virtual const std::string Chipset() const = 0;
    };
}
}