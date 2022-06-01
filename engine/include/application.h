#pragma once

#include "layer.h"
#include "mzpch.h"
#include "layerStack.h"
#include <SDL2/SDL.h>

int main(int argc, char* argv[]);

namespace  Man520 {

    struct ApplicationCommandLineArgs {
        int Count = 0;
        char** Args = nullptr;

        const char* operator[](int index) const {
                return Args[index];
        }
    };

    class Application {
        public:
            Application(const char* title, int x, int y, int w, int h);
            Application(const char* title = "Man520 Engine", ApplicationCommandLineArgs args = ApplicationCommandLineArgs());
            virtual ~Application();
            void initialize();
            void setEventCallback(std::function<void(void)> func);
            void setUpdateCallback(std::function<void(void)> func);
            void quit();

            void pushLayer(Layer* layer);
            void pushOverlay(Layer* overlay);
            void popLayer(Layer* layer);
            void popOverlay(Layer* overlay);
            inline int getMouseX() const { return mMouseX; }
            inline int getMouseY() const { return mMouseY; }
            inline int getDeltaTime() const { return mDeltaTime; }
            static SDL_Renderer* getRenderer();
        private:
            void runLoop();

            ApplicationCommandLineArgs mCommandLineArgs;
            SDL_Window* mWindow{nullptr};
            static SDL_Renderer* sRenderer;
            LayerStack mLayerStack;
            const char* mTitle;
            std::function<void(void)> mEventCallback;
            std::function<void(void)> mUpdateCallback;
            int mMouseX;
            int mMouseY;
            int mWindowX;
            int mWindowY;
            int mWindowWidth;
            int mWindowHeight;
            Uint32 mDeltaTime;
            Uint32 mMaxFrameRate;
            bool mIsAppRunning;
            friend int ::main(int argc, char* argv[]);
    };
    // To be defined in Client
    Application* CreateApplication(ApplicationCommandLineArgs args);
}
