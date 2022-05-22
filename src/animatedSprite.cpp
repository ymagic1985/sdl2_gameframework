#include "animatedSprite.h"
#include "resourceManager.h"

AnimatedSprite::AnimatedSprite(SDL_Renderer* renderer, const std::string& name) {
    SDL_Surface* surface = ResourceManager::getInstance().getSurface(name);
    mTexture = SDL_CreateTextureFromSurface(renderer, surface);
}

AnimatedSprite::~AnimatedSprite() {
    SDL_DestroyTexture(mTexture);
}

void AnimatedSprite::draw(int x, int y, int w, int h) {
    mDst.x = x;
    mDst.y = y;
    mDst.w = w;
    mDst.h = h;
}

void AnimatedSprite::playFrame(int x, int y, int w, int h, int frame) {
    mSrc.x = x + w*frame;
    mSrc.y = y;
    mSrc.w = w;
    mSrc.h = h;
}

void AnimatedSprite::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, mTexture, &mSrc, &mDst);
}
