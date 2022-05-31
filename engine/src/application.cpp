
#include "application.h"


namespace Man520 {

    Application::Application(const char* title, int x, int y, int w, int h) : mTitle(title), mWindowX(x), mWindowY(y), mWindowWidth(w), mWindowHeight(h), mIsAppRunning(true), mDeltaTime(0), mMaxFrameRate(16) {
        initialize();
    }


    Application::~Application() {
        SDL_DestroyRenderer(mRenderer);
        SDL_DestroyWindow(mWindow);
        SDL_Quit();
    }

    void Application::initialize() {
        //initialize logging system;
        Log::init();

        if(SDL_Init(SDL_INIT_VIDEO) < 0) {
            MAN520_CORE_ERROR("SDL could not be initialized!");
        } else {
            MAN520_CORE_INFO("SDL video system is ready to go!");      
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
            
            SDL_RenderClear(mRenderer);
  
            //update layers
            for(auto layer : mLayerStack) {
                layer->onUpdate();
            }

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
    
    void Application::pushLayer(Layer* layer) {
        mLayerStack.pushLayer(layer);
    }
        
    void Application::pushOverlay(Layer* overlay) {
        mLayerStack.pushOverlay(overlay);
    }

    void Application::popLayer(Layer* layer) {
        mLayerStack.popLayer(layer);
    }
    
    void Application::popOverlay(Layer* overlay) {
        mLayerStack.popOverlay(overlay);
    }

}
