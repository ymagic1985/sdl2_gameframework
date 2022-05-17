// On macOS compile with:
// g++ -std=c++17 main.cpp configure.cpp command.cpp texturedRectangle.cpp glad/src/glad.c -I ./glad/include -o prog -lsdl2  

// C++ Standard Libraries
#include <iostream>
#include <glad/glad.h>
// Third-party library
#include <SDL2/SDL.h>
#include <memory>
#include <vector>
//
#include "application.h"
#include "command.h"
#include "configure.h"
#include "texturedRectangle.h"
#include "waterEffect.h"
#include "gameObject.h"
#include "input.h"

Application* app;// = new Application("SDL Game Framework", 0, 0, 640, 480);
WaterInputComponent* wInput;// = new WaterInputComponent();
WaterPyhsicsComponent* wPyhsics;// = new WaterPyhsicsComponent();
WaterGraphicsComponent* wGraphics;// = new WaterGraphicsComponent(app->getRenderer(), "../images/pool2.bmp");

GameObject* water;// = new GameObject(wInput, wPyhsics, wGraphics);

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

void handleRendering() {
    water->update(app->getDeltaTime());
}
                     

//Initialize input
Input* Input::s_Instance = new MacInput();

int main(int argc, char* argv[]){
    
    app = new Application("SDL Game Framework", 0, 0, 640, 480);
    wInput = new WaterInputComponent();
    wPyhsics = new WaterPyhsicsComponent();
    wGraphics = new WaterGraphicsComponent(app->getRenderer(), "../images/pool2.bmp");
    water = new GameObject(wInput, wPyhsics, wGraphics);
    
    app->setEventCallback(handleEvents);
    app->setRenderCallback(handleRendering);
    app->runLoop();
    delete app;
    delete water;

    return 0;
}
