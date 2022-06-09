#include "sandboxScene.h" 
#include "core/animatedSprite.h"
#include "core/entity.h"
#include "core/input.h"
#include "core/application.h"

//just for the purpose of testing:
#include "core/gameObject.h"
#include "core/waterEffect.h"


//Input* Input::s_Instance = new MacInput();
SandboxScene::SandboxScene() {
    Man520::Entity player = createEntity();
    player.addComponent<Man520::AnimatedSprite>(Man520::Application::getRenderer(), "../images/womanSprite.bmp");

    auto water = createEntity();
    water.addComponent<Man520::WaterInputComponent>();
    water.addComponent<Man520::WaterPyhsicsComponent>();
    water.addComponent<Man520::WaterGraphicsComponent>(Man520::Application::getRenderer(), "../images/pool2.bmp");
    water.addComponent<Man520::GameObject>(&water.getComponent<Man520::WaterInputComponent>(),
                                           &water.getComponent<Man520::WaterPyhsicsComponent>(), 
                                           &water.getComponent<Man520::WaterGraphicsComponent>()); 
}

SandboxScene::~SandboxScene() {
}

//put the following into repective components
int frame = 0;
int dir = 0;
std::vector< std::vector<int> > vels = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}, {-1, -1}, {1, -1}, {-1, 1}, {1, 1}, {0, 0}};
int vIndex = 0;
int x{100}, y{100};
void SandboxScene::update() {
    auto view = mRegistry.view<Man520::GameObject>();

    for(auto entity : view) {
        auto &go = view.get<Man520::GameObject>(entity);
        go.update(16.0f);
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
    auto view2 = mRegistry.view<Man520::AnimatedSprite>();
    for(auto entity : view2) {
        auto &sprite = view2.get<Man520::AnimatedSprite>(entity);
        sprite.playFrame(0, 92*dir, 48, 92, frame/4);
        if(frame > 48) frame = 0;
        sprite.draw(x, y, 48, 92);
        sprite.render(Man520::Application::getRenderer());
    }
}
