#pragma once

#include <string>

#include <SDL2/SDL.h>

namespace Man520 {

    class AnimatedSprite {
        public:
            AnimatedSprite(SDL_Renderer* renderer, const std::string& name);
            ~AnimatedSprite();

            void draw(int x, int y, int w, int h);
            void playFrame(int x, int y, int w, int h, int frame);
            void render(SDL_Renderer* renderer);
        private:
            SDL_Rect mSrc;
            SDL_Rect mDst;
            SDL_Texture* mTexture;
    };

}

