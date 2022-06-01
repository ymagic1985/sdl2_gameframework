//On macOS compile with:
// g++ -std=c++17 main.cpp configure.cpp command.cpp texturedRectangle.cpp glad/src/glad.c -I ./glad/include -o prog -lsdl2

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
#include "scene.h"
#include "entity.h"

Man520::Application* app;
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

void handleUpdate() {
}
                     

//Initialize input
Input* Input::s_Instance = new MacInput();

int main(int argc, char* argv[]){
   
    app = Man520::CreateApplication({argc, argv});//new Man520::Application("SDL Game Framework", 0, 0, 640, 480);   
   
    app->setEventCallback(handleEvents);
    app->setUpdateCallback(handleUpdate);
    app->runLoop();
    delete app;

    return 0;
}
