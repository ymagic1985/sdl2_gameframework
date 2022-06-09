
#include "core/application.h"
#include "sandbox3D.h"
class SandboxApp : public  Man520::Application {
    public:
        SandboxApp(Man520::ApplicationCommandLineArgs args) {
            pushLayer(new Sandbox3D());
        }

        ~SandboxApp() {
        }

};

Man520::Application* Man520::CreateApplication(ApplicationCommandLineArgs args) {
    Application* app = new SandboxApp(args);
    return app;
}

