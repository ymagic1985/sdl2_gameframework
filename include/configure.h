#include <assert.h>
#define PLATFORM 1

enum PLATFORM_TYPE {
    WIN     = 1,
    MACOS   = 2,
    ANDROID = 3,
    IOS     = 4,
    NUM_OF_PLATFORMS
};

class Configure {
    public:
        virtual ~Configure() {}
        virtual int getWindowWidth() const;
        virtual int getWindowHeight() const; 
        virtual void setWindowWidth(int width); 
        virtual void setWindowHeight(int height);
        static  Configure& getInstance();
    protected:
        Configure() {}
        Configure(const Configure& rhs) {};
        
        int windowHeight_;
        int windowWidth_;
        static bool instantiated_;
};

class WinConfigure : public Configure {
    public:
        WinConfigure() {
            assert(!instantiated_);
            instantiated_ = true;
        }
        //platform specific functions
    protected:
};

