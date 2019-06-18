//
// generated automatically from "IWebPA.h"
//
// implements RPC proxy stubs for:
//   - class IWebPAService
//   - class IWebPAClient
//

#include "IWebPA.h"

namespace WPEFramework {

namespace ProxyStubs {

    using namespace Exchange;

    // -----------------------------------------------------------------
    // STUB
    // -----------------------------------------------------------------

    //
    // IWebPAService interface stub definitions
    //
    // Methods:
    //  (0) virtual uint32_t Configure(PluginHost::IShell*) = 0
    //  (1) virtual void Launch() = 0
    //

    ProxyStub::MethodHandler WebPAServiceStubMethods[] = {
        // virtual uint32_t Configure(PluginHost::IShell*) = 0
        //
        [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            RPC::Data::Input& input(message->Parameters());

            // read parameters
            RPC::Data::Frame::Reader reader(input.Reader());
            PluginHost::IShell* param0 = reader.Number<PluginHost::IShell*>();
            PluginHost::IShell* param0_proxy = nullptr;
            ProxyStub::UnknownProxy* param0_proxy_inst = nullptr;
            if (param0 != nullptr) {
                param0_proxy_inst = RPC::Administrator::Instance().ProxyInstance(channel, param0, PluginHost::IShell::ID, false, PluginHost::IShell::ID, true);
                if (param0_proxy_inst != nullptr) {
                    param0_proxy = param0_proxy_inst->QueryInterface<PluginHost::IShell>();
                }

                ASSERT((param0_proxy != nullptr) && "Failed to get instance of PluginHost::IShell proxy");
                if (param0_proxy == nullptr) {
                    TRACE_L1("Failed to get instance of PluginHost::IShell proxy");
                }
            }

            // write return value
            RPC::Data::Frame::Writer writer(message->Response().Writer());

            if ((param0 == nullptr) || (param0_proxy != nullptr)) {
                // call implementation
                IWebPAService* implementation = input.Implementation<IWebPAService>();
                ASSERT((implementation != nullptr) && "Null IWebPAService implementation pointer");
                const uint32_t output = implementation->Configure(param0_proxy);
                writer.Number<const uint32_t>(output);
            } else {
                // return error code
                writer.Number<const uint32_t>(Core::ERROR_RPC_CALL_FAILED);
            }

            if (param0_proxy_inst != nullptr) {
                RPC::Administrator::Instance().Release(param0_proxy_inst, message->Response());
            }
        },

        // virtual void Launch() = 0
        //
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            RPC::Data::Input& input(message->Parameters());

            // call implementation
            IWebPAService* implementation = input.Implementation<IWebPAService>();
            ASSERT((implementation != nullptr) && "Null IWebPAService implementation pointer");
            implementation->Launch();
        },

        nullptr
    }; // WebPAServiceStubMethods[]

    //
    // IWebPAClient interface stub definitions
    //
    // Methods:
    //  (0) virtual uint32_t Configure(PluginHost::IShell*) = 0
    //  (1) virtual void Launch() = 0
    //

    ProxyStub::MethodHandler WebPAClientStubMethods[] = {
        // virtual uint32_t Configure(PluginHost::IShell*) = 0
        //
        [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            RPC::Data::Input& input(message->Parameters());

            // read parameters
            RPC::Data::Frame::Reader reader(input.Reader());
            PluginHost::IShell* param0 = reader.Number<PluginHost::IShell*>();
            PluginHost::IShell* param0_proxy = nullptr;
            ProxyStub::UnknownProxy* param0_proxy_inst = nullptr;
            if (param0 != nullptr) {
                param0_proxy_inst = RPC::Administrator::Instance().ProxyInstance(channel, param0, PluginHost::IShell::ID, false, PluginHost::IShell::ID, true);
                if (param0_proxy_inst != nullptr) {
                    param0_proxy = param0_proxy_inst->QueryInterface<PluginHost::IShell>();
                }

                ASSERT((param0_proxy != nullptr) && "Failed to get instance of PluginHost::IShell proxy");
                if (param0_proxy == nullptr) {
                    TRACE_L1("Failed to get instance of PluginHost::IShell proxy");
                }
            }

            // write return value
            RPC::Data::Frame::Writer writer(message->Response().Writer());

            if ((param0 == nullptr) || (param0_proxy != nullptr)) {
                // call implementation
                IWebPAClient* implementation = input.Implementation<IWebPAClient>();
                ASSERT((implementation != nullptr) && "Null IWebPAClient implementation pointer");
                const uint32_t output = implementation->Configure(param0_proxy);
                writer.Number<const uint32_t>(output);
            } else {
                // return error code
                writer.Number<const uint32_t>(Core::ERROR_RPC_CALL_FAILED);
            }

            if (param0_proxy_inst != nullptr) {
                RPC::Administrator::Instance().Release(param0_proxy_inst, message->Response());
            }
        },

        // virtual void Launch() = 0
        //
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            RPC::Data::Input& input(message->Parameters());

            // call implementation
            IWebPAClient* implementation = input.Implementation<IWebPAClient>();
            ASSERT((implementation != nullptr) && "Null IWebPAClient implementation pointer");
            implementation->Launch();
        },

        nullptr
    }; // WebPAClientStubMethods[]

    // -----------------------------------------------------------------
    // PROXY
    // -----------------------------------------------------------------

    //
    // IWebPAService interface proxy definitions
    //
    // Methods:
    //  (0) virtual uint32_t Configure(PluginHost::IShell*) = 0
    //  (1) virtual void Launch() = 0
    //

    class WebPAServiceProxy final : public ProxyStub::UnknownProxyType<IWebPAService> {
    public:
        WebPAServiceProxy(const Core::ProxyType<Core::IPCChannel>& channel, void* implementation, const bool otherSideInformed)
            : BaseClass(channel, implementation, otherSideInformed)
        {
        }

        uint32_t Configure(PluginHost::IShell* param0) override
        {
            IPCMessage newMessage(BaseClass::Message(0));

            // write parameters
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<PluginHost::IShell*>(param0);

            // invoke the method handler
            uint32_t output{};
            if ((output = Invoke(newMessage)) == Core::ERROR_NONE) {
                // read return value
                RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
                output = reader.Number<uint32_t>();

                Complete(reader);
            }

            return output;
        }

        void Launch() override
        {
            IPCMessage newMessage(BaseClass::Message(1));

            // invoke the method handler
            Invoke(newMessage);
        }
    }; // class WebPAServiceProxy

    //
    // IWebPAClient interface proxy definitions
    //
    // Methods:
    //  (0) virtual uint32_t Configure(PluginHost::IShell*) = 0
    //  (1) virtual void Launch() = 0
    //

    class WebPAClientProxy final : public ProxyStub::UnknownProxyType<IWebPAClient> {
    public:
        WebPAClientProxy(const Core::ProxyType<Core::IPCChannel>& channel, void* implementation, const bool otherSideInformed)
            : BaseClass(channel, implementation, otherSideInformed)
        {
        }

        uint32_t Configure(PluginHost::IShell* param0) override
        {
            IPCMessage newMessage(BaseClass::Message(0));

            // write parameters
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<PluginHost::IShell*>(param0);

            // invoke the method handler
            uint32_t output{};
            if ((output = Invoke(newMessage)) == Core::ERROR_NONE) {
                // read return value
                RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
                output = reader.Number<uint32_t>();

                Complete(reader);
            }

            return output;
        }

        void Launch() override
        {
            IPCMessage newMessage(BaseClass::Message(1));

            // invoke the method handler
            Invoke(newMessage);
        }
    }; // class WebPAClientProxy

    // -----------------------------------------------------------------
    // REGISTRATION
    // -----------------------------------------------------------------

    namespace {

        typedef ProxyStub::UnknownStubType<IWebPAClient, WebPAClientStubMethods> WebPAClientStub;
        typedef ProxyStub::UnknownStubType<IWebPAService, WebPAServiceStubMethods> WebPAServiceStub;

        static class Instantiation {
        public:
            Instantiation()
            {
                RPC::Administrator::Instance().Announce<IWebPAClient, WebPAClientProxy, WebPAClientStub>();
                RPC::Administrator::Instance().Announce<IWebPAService, WebPAServiceProxy, WebPAServiceStub>();
            }
        } ProxyStubRegistration;

    } // namespace

} // namespace ProxyStubs

}
