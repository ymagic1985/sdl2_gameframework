#include "resourceManager.h"
#include "texturedRectangle.h"

namespace Man520 {

    TexturedRectangle::TexturedRectangle(SDL_Renderer*& renderer, const std::string& name) : mTexture(nullptr) {
        SDL_Surface* surface = ResourceManager::getInstance().getSurface(name);
        mTexture = SDL_CreateTextureFromSurface(renderer, surface);
    }

    TexturedRectangle::TexturedRectangle(const TexturedRectangle& rhs) {
        this->operator=(rhs);
    }

    TexturedRectangle::TexturedRectangle(TexturedRectangle&& rhs) {
        this->mRect = rhs.mRect;
        this->mTexture = rhs.mTexture;
     
        rhs.mRect.x = 0;
        rhs.mRect.y = 0;
        rhs.mRect.w = 0;
        rhs.mRect.h = 0;
        rhs.mTexture = nullptr;
    }

    TexturedRectangle& TexturedRectangle::operator= (const TexturedRectangle& rhs) {
        if(this != &rhs) {
            this->mRect = rhs.mRect;
            this->mTexture = rhs.mTexture;
        }
        return *this;
    }
           
    TexturedRectangle& TexturedRectangle::operator= (TexturedRectangle&& rhs) {
        if(this != &rhs) {
            this->mRect = rhs.mRect;
            this->mTexture = rhs.mTexture;

            rhs.mRect.x = 0;
            rhs.mRect.y = 0;
            rhs.mRect.w = 0;
            rhs.mRect.h = 0;
            rhs.mTexture = nullptr;
        }
        return *this;
    }

    TexturedRectangle::~TexturedRectangle() {
        SDL_DestroyTexture(mTexture);
    }

    void TexturedRectangle::setRectangeProperties(int x, int y, int w, int h) {
        mRect.x = x;
        mRect.y = y;
        mRect.w = w;
        mRect.h = h;
    }

    void TexturedRectangle::render(SDL_Renderer*& renderer) {
        SDL_RenderCopy(renderer, mTexture, NULL, &mRect);
    }

    void TexturedRectangle::update() {
    }

}
