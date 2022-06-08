#pragma once
#include "renderer/graphicsContext.h"
#include <SDL2/SDL.h>

namespace Man520 {
        
    class OpenGLContext : public GraphicsContext {
        public:
            OpenGLContext(SDL_Window* windowHandle);
            ~OpenGLContext();

            virtual void init() override;
            virtual void swapBuffers() override;
        private:
            SDL_Window* mWindowHandle;
            SDL_GLContext mGLContext;
    };

}
