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
}
}
