
#include "application.h"
#include "sandbox2D.h"
class SandboxApp : public  Man520::Application {
    public:
        SandboxApp(Man520::ApplicationCommandLineArgs args) {
            pushLayer(new Sandbox2D());
        }

        ~SandboxApp() {
        }

};

Man520::Application* Man520::CreateApplication(ApplicationCommandLineArgs args) {
    Application* app = new SandboxApp(args);
    return app;
}

