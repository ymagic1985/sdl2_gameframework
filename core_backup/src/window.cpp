#include "window.h" 
#include "application.h"

#include <SDL2/SDL.h>
namespace Man520 {

    Window::Window(const std::string& title, uint32_t w, uint32_t h) {
        mProps.mTitle = title;
        mProps.mWidth = w;
        mProps.mHeight = h;

        mWindow = SDL_CreateWindow(title.c_str(), 
                SDL_WINDOWPOS_UNDEFINED, 
                SDL_WINDOWPOS_UNDEFINED,
                w,
                h,
                SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
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
            SDL_RenderPresent(Application::getRenderer());
            break;
        //Repaint on exposure
        case SDL_WINDOWEVENT_EXPOSED:
            SDL_RenderPresent(Application::getRenderer());
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
    }

}
