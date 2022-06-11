#pragma once
#include "mzpch.h"
#include "renderer/rendererAPI.h"
#include "renderer/graphicsContext.h"

class SDL_Window;
typedef union SDL_Event SDL_Event;
namespace Man520 {

    struct WindowProps {
        std::string mTitle;
        uint32_t mWidth;
        uint32_t mHeight;

        WindowProps(const std::string& title = "Man520 Engine", uint32_t w = 1280, uint32_t h = 720) : mTitle(title), mWidth(w), mHeight(h) {}
    };

    class Window {
        public:
            Window(const std::string& title, uint32_t w, uint32_t h, RendererAPI::API api = RendererAPI::API::OpenGL); 

            virtual ~Window();

            virtual void onUpdate();

            uint32_t getWidth() const { return mProps.mWidth; }
            uint32_t getHeight() const { return mProps.mHeight; }
            
            void fullScreenSwitch();
            void handleEvent(SDL_Event& e);
            inline SDL_Window*& getSDLWindow() { return mWindow; }
            inline GraphicsContext& getGraphicsContext() { return *mContext; }
            void* getSDLGLContext();
            inline bool isFullscreen() const { return mFullScreen; }
            inline bool isMinimized() const { return mMinimized; }

        private:
            SDL_Window* mWindow;
            Scope<GraphicsContext> mContext;
            WindowProps mProps;
            //not used yet
            bool mKeyboardFocus = false;
            bool mMouseFocus = false;
            bool mFullScreen = false;
            bool mMinimized = false;
    };

}
