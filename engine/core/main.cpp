//On macOS compile with:
// g++ -std=c++17 main.cpp configure.cpp command.cpp texturedRectangle.cpp glad/src/glad.c -I ./glad/include -o prog -lsdl2
#include "application.h"
#include "input.h"

Man520::Application* app;
Input* Input::s_Instance = new MacInput();

int main(int argc, char* argv[]){
   
    app = Man520::CreateApplication({argc, argv});
    app->runLoop();
    delete app;

    return 0;
}
