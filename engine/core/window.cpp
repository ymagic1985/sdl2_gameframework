#include "window.h" 
#include "application.h"
#include "renderer/renderer.h"
#include "platform/openGL/openGLContext.h"
#include <SDL2/SDL.h>
namespace Man520 {

    Window::Window(const std::string& title, uint32_t w, uint32_t h, RendererAPI::API api) {
        mProps.mTitle = title;
        mProps.mWidth = w;
        mProps.mHeight = h;

        SDL_WindowFlags flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
        /*switch(api) {
            case RendererAPI::API::OpenGL: flags |= SDL_WINDOW_OPENGL; break;
            default: MAN520_CORE_ASSERT(false, "Unknown RendererAPI::API in Window()"); break;
        }*/
        //TODO: Switch graphics API
        mWindow = SDL_CreateWindow(title.c_str(), 
                SDL_WINDOWPOS_CENTERED, 
                SDL_WINDOWPOS_CENTERED,
                w,
                h,
                flags);
        mContext = GraphicsContext::create(mWindow);
        mContext->init();
    }
    
    Window::~Window() {
        SDL_DestroyWindow(mWindow);   
    }
        
    void Window::fullScreenSwitch() {
        mFullScreen = !mFullScreen;
        SDL_SetWindowFullscreen(mWindow, mFullScreen);
    }
        
    void Window::handleEvent(SDL_Event& event) {
        //Caption update flag
        bool updateCaption = false;
        switch(event.window.event) {
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            mProps.mWidth = event.window.data1;
            mProps.mHeight = event.window.data2;
            Renderer::onWindowResize(mProps.mWidth, mProps.mHeight);
            //SDL_RenderPresent(Application::getRenderer());
            break;
        //Repaint on exposure
        case SDL_WINDOWEVENT_EXPOSED:
            Renderer::onWindowResize(mProps.mWidth, mProps.mHeight);
            //SDL_RenderPresent(Application::getRenderer());
            break;
        //Mouse entered window
        case SDL_WINDOWEVENT_ENTER:
            mMouseFocus = true;
            updateCaption = true;
            break;
            
        //Mouse left window
        case SDL_WINDOWEVENT_LEAVE:
            mMouseFocus = false;
            updateCaption = true;
            break;

        //Window has keyboard focus
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            mKeyboardFocus = true;
            updateCaption = true;
            break;

        //Window lost keyboard focus
        case SDL_WINDOWEVENT_FOCUS_LOST:
            mKeyboardFocus = false;
            updateCaption = true;
            break;
        }

        if(updateCaption )
        {
            std::stringstream caption;
            caption <<mProps.mTitle <<" - MouseFocus:" << ( ( mMouseFocus ) ? "On" : "Off" ) << " KeyboardFocus:" << ( ( mKeyboardFocus ) ? "On" : "Off" );
            SDL_SetWindowTitle(mWindow, caption.str().c_str() );
        }
    }

    void Window::onUpdate() {
        mContext->swapBuffers();
    }
    
    void* Window::getSDLGLContext() {
        return static_cast<OpenGLContext&>(*mContext).getSDL_GLContext();
    }
}
