#include "Module.h"
#include "IShell.h"

namespace WPEFramework {

ENUM_CONVERSION_BEGIN(PluginHost::IShell::state)

    { PluginHost::IShell::DEACTIVATED, _TXT("Deactivated") },
    { PluginHost::IShell::DEACTIVATION, _TXT("Deactivation") },
    { PluginHost::IShell::ACTIVATED, _TXT("Activated") },
    { PluginHost::IShell::ACTIVATION, _TXT("Activation") },
    { PluginHost::IShell::PRECONDITION, _TXT("Precondition") },
    { PluginHost::IShell::DESTROYED, _TXT("Destroyed") },

ENUM_CONVERSION_END(PluginHost::IShell::state)

ENUM_CONVERSION_BEGIN(PluginHost::IShell::reason)

    { PluginHost::IShell::REQUESTED, _TXT("Requested") },
    { PluginHost::IShell::AUTOMATIC, _TXT("Automatic") },
    { PluginHost::IShell::FAILURE, _TXT("Failure") },
    { PluginHost::IShell::MEMORY_EXCEEDED, _TXT("MemoryExceeded") },
    { PluginHost::IShell::STARTUP, _TXT("Startup") },
    { PluginHost::IShell::SHUTDOWN, _TXT("Shutdown") },
    { PluginHost::IShell::CONDITIONS, _TXT("Conditions") },

ENUM_CONVERSION_END(PluginHost::IShell::reason)

namespace PluginHost
{
    void* IShell::Root(uint32_t & pid, const uint32_t waitTime, const string className, const uint32_t interface, const uint32_t version)
    {
        void* result = nullptr;
        Object rootObject(this);

        bool inProcessOldConfiguration = ( !rootObject.Mode.IsSet() ) && ( rootObject.OutOfProcess.Value() == false ); //note: when both new and old not set this one will revert to the old default which was true
        bool inProcessNewConfiguration = ( rootObject.Mode.IsSet() ) && ( rootObject.Mode == Object::ModeType::OFF ); // when both set the Old one is ignored

        if ( (inProcessNewConfiguration == true) || (inProcessOldConfiguration == true) ) {

            string locator(rootObject.Locator.Value());

            if (locator.empty() == true) {
                result = Core::ServiceAdministrator::Instance().Instantiate(Core::Library(), className.c_str(), version, interface);
            } else {
                string search(PersistentPath() + locator);
                Core::Library resource(search.c_str());

                if (!resource.IsLoaded()) {
                    search = DataPath() + locator;
                    resource = Core::Library(search.c_str());

                    if (!resource.IsLoaded()) {
                        resource = Core::Library(locator.c_str());
                    }
                }
                if (resource.IsLoaded() == true) {
                    result = Core::ServiceAdministrator::Instance().Instantiate(resource, className.c_str(), version, interface);
                }
            }
        } else {
            ICOMLink* handler(COMLink());

            // This method can only be used in the main process. Only this process, can instantiate a new process
            ASSERT(handler != nullptr);

            if (handler != nullptr) {
                string locator(rootObject.Locator.Value());
                if (locator.empty() == true) {
                    locator = Locator();
                }
                RPC::Object definition(Callsign(), locator,
                    className,
                    interface,
                    version,
                    rootObject.User.Value(),
                    rootObject.Group.Value(),
                    rootObject.Threads.Value(),
                    rootObject.Priority.Value(),
                    rootObject.HostType(), 
                    rootObject.Configuration.Value());

                result = handler->Instantiate(definition, waitTime, pid, ClassName(), Callsign());
            }
        }

        return (result);
    }

    // Method for starting a remote process with a diffrent connector
    void* IShell::Root(const string& address, uint32_t& pid, const uint32_t waitTime, const string className, const uint32_t interface, const uint32_t version) {
        ICOMLink* handler(COMLink());
        void* result = nullptr;
        Object rootObject(this);

        // This method can only be used in the main process. Only this process, can instantiate a new process
        ASSERT(handler != nullptr);

        if (handler != nullptr) {
            string locator(rootObject.Locator.Value());
            if (locator.empty() == true) {
                locator = Locator();
            }
            RPC::Object definition(Callsign(), locator,
                className,
                interface,
                version,
                rootObject.User.Value(),
                rootObject.Group.Value(),
                rootObject.Threads.Value(),
                RPC::Object::HostType::DISTRIBUTED,
                address,
                rootObject.Configuration.Value());

            result = handler->Instantiate(definition, waitTime, pid, ClassName(), Callsign());
        }

        return result;
    }
}

ENUM_CONVERSION_BEGIN(PluginHost::Object::ModeType)

    { PluginHost::Object::ModeType::OFF, _TXT("Off") },
    { PluginHost::Object::ModeType::LOCAL, _TXT("Local") },
    { PluginHost::Object::ModeType::CONTAINER, _TXT("Container") },
    { PluginHost::Object::ModeType::DISTRIBUTED, _TXT("Distributed") },

ENUM_CONVERSION_END(PluginHost::Object::ModeType);

} // namespace 



