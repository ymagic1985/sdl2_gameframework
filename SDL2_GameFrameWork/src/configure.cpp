#include "configure.h"

bool Configure::instantiated_ = false;
int Configure::getWindowWidth() const {
    return windowWidth_;
}

int Configure::getWindowHeight() const {
    return windowHeight_;
}

void Configure::setWindowWidth(int width) {
    windowWidth_ = width;
}

void Configure::setWindowHeight(int height) {
    windowHeight_ = height;
}

Configure& Configure::getInstance() {
#if PLATFORM == 1 //WINDOWS
    static Configure* instance = new WinConfigure();
#elif PLATFORM == 2 //MACOS
#endif
    return *instance;
}

