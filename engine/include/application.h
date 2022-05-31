#pragma once

#include "layer.h"
#include "mzpch.h"
#include "layerStack.h"
#include <SDL2/SDL.h>

namespace  Man520 {

    class Application {
        public:
            Application(const char* title, int x, int y, int w, int h);
            ~Application();
            void initialize();
            void setEventCallback(std::function<void(void)> func);
            void setUpdateCallback(std::function<void(void)> func);
            void runLoop();
            void quit();

            void pushLayer(Layer* layer);
            void pushOverlay(Layer* overlay);
            void popLayer(Layer* layer);
            void popOverlay(Layer* overlay);
            inline int getMouseX() const { return mMouseX; }
            inline int getMouseY() const { return mMouseY; }
            inline int getDeltaTime() const { return mDeltaTime; }
            inline SDL_Renderer* getRenderer() const { return mRenderer; }
        private:
            SDL_Window* mWindow = nullptr;
            SDL_Renderer*  mRenderer = nullptr;
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
    };

}
