
#include <functional>

#include <SDL2/SDL.h>

class Application {
    public:
        Application(const char* title, int x, int y, int w, int h);
        ~Application();
        void initialize();
        void setEventCallback(std::function<void(void)> func);
        void setRenderCallback(std::function<void(void)> func);
        void runLoop();
        void quit();
        inline int getMouseX() const { return mMouseX; }
        inline int getMouseY() const { return mMouseY; }
        inline SDL_Renderer* getRenderer() const { return mRenderer; }
    private:
        SDL_Window* mWindow = nullptr;
        SDL_Renderer*  mRenderer = nullptr;
        const char* mTitle;
        std::function<void(void)> mEventCallback;
        std::function<void(void)> mRenderCallback;
        int mMouseX;
        int mMouseY;
        int mWindowX;
        int mWindowY;
        int mWindowWidth;
        int mWindowHeight;
        Uint32 mTickTime;
        Uint32 mMaxFrameRate;
        bool mIsAppRunning;
};
