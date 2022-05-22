// On macOS compile with:
// g++ -std=c++17 main.cpp configure.cpp command.cpp texturedRectangle.cpp glad/src/glad.c -I ./glad/include -o prog -lsdl2  

// C++ Standard Libraries
#include <iostream>
#include <memory>
#include <vector>

// Third-party library
#include <SDL2/SDL.h>
#include <glad/glad.h> //OpenGL
#include <entt.hpp> //Entt ECS header

#include "application.h"
#include "command.h"
#include "configure.h"
#include "texturedRectangle.h"
#include "waterEffect.h"
#include "gameObject.h"
#include "input.h"
#include "animatedSprite.h"

Application* app;
entt::registry entt_registry;

void initializeConfig() {
    Configure::getInstance().setWindowWidth(640);
    Configure::getInstance().setWindowHeight(480);
}

void setPixel(SDL_Surface* surface, int x, int y, uint8_t r, uint8_t g, uint8_t b) {
    SDL_LockSurface(surface);
    uint8_t* pixelArray = (uint8_t*)surface->pixels;
    pixelArray[y*surface->pitch + x*surface->format->BytesPerPixel+0] = g;
    pixelArray[y*surface->pitch + x*surface->format->BytesPerPixel+1] = b;
    pixelArray[y*surface->pitch + x*surface->format->BytesPerPixel+2] = r;
    SDL_UnlockSurface(surface);
}

void handleEvents() {
    SDL_Event event;
    while (SDL_PeepEvents(&event, 1, SDL_GETEVENT, 0, SDL_LASTEVENT) == 1){
        //Handle each specific event
        switch(event.type) {
            case SDL_QUIT:
                app->quit();
                break;
        }
    }
}

int frame = 0;
int dir = 0;
std::vector< std::vector<int> > vels = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}, {-1, -1}, {1, -1}, {-1, 1}, {1, 1}, {0, 0}};
int vIndex = 0;
int x{100}, y{100};
void handleUpdate() {
    //water->update(app->getDeltaTime());
    auto view = entt_registry.view<GameObject>();

    for(auto entity : view) {
       auto &gameObject = view.get<GameObject>(entity);
       gameObject.update(app->getDeltaTime());
    }

    if(Input::isKeyboardPressed(SDL_SCANCODE_UP)) {
        if(Input::isKeyboardPressed(SDL_SCANCODE_LEFT)) { dir = 3; vIndex = 4; frame++; }
        else if (Input::isKeyboardPressed(SDL_SCANCODE_RIGHT)) { dir = 5; vIndex = 5; frame++; }
        else { dir = 4; vIndex = 1; frame++; } 
    }
    else if(Input::isKeyboardPressed(SDL_SCANCODE_DOWN)) { 
        if(Input::isKeyboardPressed(SDL_SCANCODE_LEFT)) { dir = 1; vIndex = 6; frame++; }
        else if (Input::isKeyboardPressed(SDL_SCANCODE_RIGHT)) { dir = 7; vIndex = 7; frame++; }
        else { dir = 0; vIndex = 0; frame++; }
    }
    else if(Input::isKeyboardPressed(SDL_SCANCODE_LEFT)) { dir = 2; vIndex = 2; frame++; }
    else if(Input::isKeyboardPressed(SDL_SCANCODE_RIGHT)) { dir = 6; vIndex = 3; frame++; }
    else { vIndex = 8; };
    
    x += vels[vIndex][0];
    y += vels[vIndex][1];
    auto view2 = entt_registry.view<AnimatedSprite>();
    for(auto entity : view2) {
        auto &sprite = view2.get<AnimatedSprite>(entity);
        sprite.playFrame(0, 92*dir, 48, 92, frame/4);
        if(frame > 48) frame = 0;
        sprite.draw(x, y, 48, 92);
        sprite.render(app->getRenderer());
    }
}
                     

//Initialize input
Input* Input::s_Instance = new MacInput();

int main(int argc, char* argv[]){
   
    app = new Application("SDL Game Framework", 0, 0, 640, 480);
   
    const auto entity = entt_registry.create();
    entt_registry.emplace<WaterInputComponent>(entity);
    entt_registry.emplace<WaterPyhsicsComponent>(entity);
    entt_registry.emplace<WaterGraphicsComponent>(entity, app->getRenderer(), "../images/pool2.bmp");
    entt_registry.emplace<GameObject>(entity, &entt_registry.get<WaterInputComponent>(entity),
                                              &entt_registry.get<WaterPyhsicsComponent>(entity),
                                              &entt_registry.get<WaterGraphicsComponent>(entity));
   
    const auto player = entt_registry.create();
    entt_registry.emplace<AnimatedSprite>(player, app->getRenderer(), "../images/womanSprite.bmp");
    
    app->setEventCallback(handleEvents);
    app->setUpdateCallback(handleUpdate);
    app->runLoop();
    delete app;

    return 0;
}
