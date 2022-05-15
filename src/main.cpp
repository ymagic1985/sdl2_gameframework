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
#include "command.h"
#include "configure.h"
#include "texturedRectangle.h"
#include "waterEffect.h"
//#include "input.h"

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
//Initialize input
Input* Input::s_Instance = new MacInput();

int main(int argc, char* argv[]){

    // Create a window data type
    // This pointer will point to the 
    // window that is allocated from SDL_CreateWindow
    SDL_Window* window=nullptr;
    SDL_Surface* screen;
        
    initializeConfig();
    // Initialize the video subsystem.
    // If it returns less than 1, then an
    // error code will be received.
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not be initialized: " <<
                  SDL_GetError();
    }else{
        std::cout << "SDL video system is ready to go\n";
    }
    
    //before create a opengl window, specify opengl version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,24);

    // Request a window to be created for our platform
    // The parameters are for the title, x and y position,
    // and the width and height of the window.
    window = SDL_CreateWindow("C++ SDL2 Window",
            0,
            0,
            Configure::getInstance().getWindowWidth(),
            Configure::getInstance().getWindowHeight(),
            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

     //OpenGL setup the graphics context
      SDL_GLContext context;
      context =SDL_GL_CreateContext(window);
    //must get the function pointers before calling gl functions otherwise sergmentation fault would occur
    gladLoadGLLoader(SDL_GL_GetProcAddress);

    /*    
    SDL_BlitSurface(image, NULL, screen, NULL);
    SDL_FreeSurface(image);*/
        
    //SDL_RENDER
    SDL_Renderer* renderer = nullptr;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    //upload the pixels to the gpu
    // set the color key after loading the surface, and before the texture
    //SDL_SetColorKey(surface, SDL_TRUE,SDL_MapRGB(surface->format, 0xFF, 0, 0xFF));
    WaterEffect water(renderer, "../images/pool2.bmp");

    bool gameIsRunnging = true;
    //main game loop
    while (gameIsRunnging){
        //opengl viewport
        glViewport(0, 
                0,
                Configure::getInstance().getWindowWidth(), 
                Configure::getInstance().getWindowHeight());
	
        //Start event loop
	SDL_Event event;
        //(1) hanlde inputs and start out event loop
        //get mouse position
        SDL_PumpEvents();
    	while (SDL_PeepEvents(&event, 1, SDL_GETEVENT, 0, SDL_LASTEVENT) == 1){
	  //Handle each specific event
	  switch(event.type) {
		 case SDL_QUIT:
			  gameIsRunnging = false;
			  break;
                 case SDL_MOUSEMOTION:
                          //rectangle2.x = event.motion.x - rectangle2.w/2;
                          //rectangle2.y = event.motion.y - rectangle2.h/2;
                          //std::cout<<"mouse.x:"<<event.motion.x<<"  mouse.y: "<<event.motion.y<<"\n";
                          break;
                /* case SDL_MOUSEBUTTONDOWN:
                          switch (event.button.button) {
                              case SDL_BUTTON_LEFT:
                                 water.setBlendMode(SDL_BLENDMODE_ADD);
                                 break;
                              case SDL_BUTTON_MIDDLE:
                                 water.setBlendMode(SDL_BLENDMODE_BLEND);
                                 break;
                              case SDL_BUTTON_RIGHT:
                                  water.setBlendMode(SDL_BLENDMODE_MOD);
                                 break;
                          } 
                          break;*/
                 default:
                          //SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE);
                          break;
	  }   
          glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
          glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
          
          //swap opengl window since we have double buffer setup here
          SDL_GL_SwapWindow(window);
    	}
    /*    if(Input::isMouseLeftPressed()) {
            water.setBlendMode(SDL_BLENDMODE_ADD);
        }
        if(Input::isMouseRightPressed()) {
            water.setBlendMode(SDL_BLENDMODE_MOD);
        }
        if(Input::isMouseMiddlePressed()) {
            water.setBlendMode(SDL_BLENDMODE_BLEND);
        }
        if(Input::isKeyboardPressed(SDL_SCANCODE_W)) {
            std::cout<<"W is pressed!\n";
        }
*/
        std::cout<<"X: "<<Input::getMouseX()<<"  Y: "<<Input::getMouseY()<<"\n";
        //(2) handle Updates
        water.update();
        //(3) Clear and Draw the Screen
        //clear the screen, make it all black
        SDL_SetRenderDrawColor(renderer, 0, 0, 0xFF, SDL_ALPHA_OPAQUE); 
        SDL_RenderClear(renderer);

        //Draw a white line test
        //SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        //SDL_RenderDrawLine(renderer, 5, 5, 300, 320);
        
        //int w, h; 
        //SDL_QueryTexture(texture, NULL, NULL, &w, &h);
        SDL_Delay(20);


        water.render(renderer);
        //Finally show what we've drawn
        SDL_RenderPresent(renderer);
        SDL_UpdateWindowSurface(window);
    }

    // We destroy our window. We are passing in the pointer
    // that points to the memory allocated by the 
    // 'SDL_CreateWindow' function. Remember, this is
    // a 'C-style' API, we don't have destructors.
    SDL_DestroyWindow(window);
    
    // We safely uninitialize SDL2, that is, we are
    // taking down the subsystems here before we exit
    // our program.
    SDL_Quit();
    return 0;
}
