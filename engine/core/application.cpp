
#include "application.h"
#include "assert.h"
#include "renderer/renderer.h"

namespace Man520 {

    SDL_Renderer* Application::sRenderer = nullptr;

    Application::Application(const char* title, int x, int y, int w, int h) : mTitle(title), mWindowX(x), mWindowY(y), mWindowWidth(w), mWindowHeight(h), mIsAppRunning(true), mDeltaTime(0), mMaxFrameRate(16) {
        initialize();
    }

    Application::Application(const char* title, ApplicationCommandLineArgs args) : Application(title, 0, 0, 640, 480) {
        mCommandLineArgs = args;
    }

    Application::~Application() {
        SDL_DestroyRenderer(sRenderer);
        SDL_Quit();
    }

    void Application::initialize() {
        Log::init();

        if(SDL_Init(SDL_INIT_VIDEO) < 0) {
            MAN520_CORE_ASSERT(false, std::string("Unable to initialize SDL video: ") + std::string(SDL_GetError()));
        } else {
            MAN520_CORE_INFO("SDL video system is ready to go!");      
        }
        
        mWindow = createScope<Window>(std::string(mTitle), mWindowWidth, mWindowHeight);
        Renderer::init();
        //sRenderer = SDL_CreateRenderer(mWindow->getSDLWindow(), -1, SDL_RENDERER_ACCELERATED); 
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
            dispatchSDLEvents();
            if(!mWindow->isMinimized()) {
        //      SDL_RenderClear(sRenderer);
		RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		RenderCommand::clear();
                //update layers
                for(auto layer : mLayerStack) {
                    layer->onUpdate();
                }

                mUpdateCallback();

       //        SDL_RenderPresent(sRenderer);
                mWindow->onUpdate();               
                //todo: handle frame cap here
                mDeltaTime = SDL_GetTicks() - start;
                if(mDeltaTime < mMaxFrameRate) 
                    SDL_Delay(mMaxFrameRate - mDeltaTime);
            }
        }
    }

    void Application::dispatchSDLEvents() {
        SDL_PumpEvents();
        SDL_GetMouseState(&mMouseX, &mMouseY);
        SDL_Event event;
        while (SDL_PeepEvents(&event, 1, SDL_GETEVENT, 0, SDL_LASTEVENT) == 1){
            switch(event.type) {
                case SDL_QUIT:
                    this->quit();
                    break;
                case SDL_WINDOWEVENT:
                    mWindow->handleEvent(event);
                    break;
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_RETURN)
                        mWindow->fullScreenSwitch();
                    break;
            }
        }
    }


    SDL_Renderer* Application::getRenderer() {
        return sRenderer;
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
