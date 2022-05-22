
#include <iostream>

#include "application.h"

namespace Man520 {

    Application::Application(const char* title, int x, int y, int w, int h) : mTitle(title), mWindowX(x), mWindowY(y), mWindowWidth(w), mWindowHeight(h), mIsAppRunning(true), mDeltaTime(0), mMaxFrameRate(16) {
        initialize();
    }


    Application::~Application() {
        SDL_DestroyWindow(mWindow);
        SDL_Quit();
    }

    void Application::initialize() {
        if(SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cout<<"SDL could not be initialized: "<<SDL_GetError()<<"\n";
        } else {
            std::cout<<"SDL video system is ready to go!\n";
        }
        
        mWindow = SDL_CreateWindow(mTitle, 
                mWindowX,
                mWindowY,
                mWindowWidth,
                mWindowHeight,
                SDL_WINDOW_SHOWN);

        mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
        
    }

    void Application::setEventCallback(std::function<void(void)> func) {
        mEventCallback = func;
    }

    void Application::setUpdateCallback(std::function<void(void)> func) {
        mUpdateCallback = func;
    }

    void Application::runLoop() {
        while(mIsAppRunning) {
            Uint32 start = SDL_GetTicks();
            SDL_PumpEvents();
            SDL_GetMouseState(&mMouseX, &mMouseY);
            
            mEventCallback();
            
            SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderClear(mRenderer);

            SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

            mUpdateCallback();

            SDL_RenderPresent(mRenderer);
            //todo: handle frame cap here
            mDeltaTime = SDL_GetTicks() - start;
            if(mDeltaTime < mMaxFrameRate) 
                SDL_Delay(mMaxFrameRate - mDeltaTime);
        }
    }

    void Application::quit() {
        mIsAppRunning = false;
    }

}