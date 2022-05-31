#pragma once

#include "mzpch.h"
#include <SDL2/SDL.h>

namespace Man520 {

    class GameObject;
    class Component {
        public:
            virtual ~Component() {}
            virtual void receive(int message) = 0; //placeholer for messages, implement event queue to replace the int message here
    };

    class InputComponent : public Component {
        public:
            virtual ~InputComponent() {}
            virtual void receive(int message) override {}
            virtual void update(GameObject* obj) = 0;
    };

    class PhysicsComponent : public Component {
        public:
            virtual ~PhysicsComponent() {}
            virtual void receive(int message) override {};
            virtual void update(Uint32 dt, GameObject* obj) = 0;
    };

    class GraphicsComponent : public Component {
        public:
            virtual ~GraphicsComponent() {}
            virtual void receive(int message) override {};
            virtual void update(GameObject* obj) = 0;
    };
    
    class TagComponent : public Component {
        public:
            void receive(int message) override {}
            std::string mTag;
    };

/**************Data Components*********************/

    struct PostionComponent {
        int x;
        int y;
    };


    struct TextureComponent {
        Ref<SDL_Texture> texture;
        Ref<SDL_Rect> src;
        Ref<SDL_Rect> dst;
        int frame;
    };

/*************Logic Components********************/ 

    struct RenderComponent {
        TextureComponent* txtComp;
        void render(SDL_Renderer* renderer) {
            SDL_RenderCopy(renderer, 
                           txtComp->texture.get(),
                           txtComp->src.get(),
                           txtComp->dst.get());
        }

        void draw(int x, int y, int w, int h) {
            txtComp->dst->x = x;
            txtComp->dst->y = y;
            txtComp->dst->w = w;
            txtComp->dst->h = h;
        }

        void playFrame(int x, int y, int w, int h, int frame) {
            txtComp->src->x = x + w * frame;
            txtComp->src->y = y;
            txtComp->src->w = w;
            txtComp->src->h = h;
        }
    };
}
