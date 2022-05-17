#include <iostream>
#include <SDL2/SDL.h>
#include "waterEffect.h"
#include "texturedRectangle.h"
#include "gameObject.h"

void WaterInputComponent::receive(int message) {
}

void WaterInputComponent::update(GameObject* obj) {
    int message = 0;
    if(Input::isMouseLeftPressed())   message = int(0x03000000);
    if(Input::isMouseMiddlePressed()) message = int(0x04000000);
    if(Input::isMouseRightPressed())  message = int(0x05000000);
    if(Input::isKeyboardPressed(SDL_SCANCODE_W)) message = int(0x02000000) | int(0x00FFFFFF);
    if(Input::isKeyboardPressed(SDL_SCANCODE_S)) message = int(0x02000000) | int(0x00000001);
    if(Input::isKeyboardPressed(SDL_SCANCODE_A)) message = int(0x01000000) | int(0x00FFFFFF);
    if(Input::isKeyboardPressed(SDL_SCANCODE_D)) message = int(0x01000000) | int(0x00000001);       

    obj->sendMessage(this, message);
}

WaterPyhsicsComponent::WaterPyhsicsComponent() : mHori_velocity(0.0f), mVert_velocity(0.0f) {
}

WaterPyhsicsComponent::~WaterPyhsicsComponent() {
}

void WaterPyhsicsComponent::receive(int message) {
    int m_type = message>>24;
    int acceleration = int(0x00FFFFFF) & message;
    acceleration <<= 8;
    acceleration >>= 8;
    switch(m_type) {
        case 1:
            std::cout<<"Horizontal acceleration: "<<acceleration<<"   velocity: "<<mHori_velocity<<"\n";
            mHori_velocity += (int)acceleration;
            break;
        case 2:
            std::cout<<"Vertical acceleration: "<<acceleration<<"   velocity: "<<mVert_velocity<<"\n";
            mVert_velocity += (int)acceleration;
            break;
    }
}

void WaterPyhsicsComponent::update(double dt, GameObject* obj) {
    int x = obj->getPosX() + mHori_velocity;
    int y = obj->getPosY() + mVert_velocity;
    
    if(x > 640) x = -640;
    if(y > 480) y = -480;
    //std::cout<<"Horizontal: "<<mHori_velocity<<"  Vertical: "<<mVert_velocity<<"\n";
    obj->setPosX(x);
    obj->setPosY(y);
    //std::cout<<"X: "<<obj->getPosX() <<"  Y: "<<obj->getPosY()<<"\n";
}

WaterGraphicsComponent::WaterGraphicsComponent(SDL_Renderer* renderer, const std::string& name) : mRenderer(renderer) {
    std::shared_ptr<TexturedRectangle> rect1 = std::make_shared<TexturedRectangle>(renderer, name.c_str());
    std::shared_ptr<TexturedRectangle> rect2 = std::make_shared<TexturedRectangle>(renderer, name.c_str());
    std::shared_ptr<TexturedRectangle> rect3 = std::make_shared<TexturedRectangle>(renderer, name.c_str());
    std::shared_ptr<TexturedRectangle> rect4 = std::make_shared<TexturedRectangle>(renderer, name.c_str());

    rect1->setRectangeProperties(0, 0, 640, 480);
    rect2->setRectangeProperties(-640, 0, 640, 480);

    rect3->setRectangeProperties(0, 0, 640, 480);
    rect4->setRectangeProperties(0,-480, 640, 480);
 
    m_bg_rects.push_back(rect1);
    m_bg_rects.push_back(rect2);
    
    m_fg_rects.push_back(rect3);
    m_fg_rects.push_back(rect4);
    
    mFG_blendMode = SDL_BLENDMODE_NONE;
}    

void WaterGraphicsComponent::receive(int message) {
    int m_type = message >> 24;
    SDL_BlendMode mode;
    switch(m_type) {
        case 3:
            mFG_blendMode = SDL_BLENDMODE_NONE;
            break;
        case 4:
            mFG_blendMode = SDL_BLENDMODE_MOD;
            break;
        case 5:
            mFG_blendMode = SDL_BLENDMODE_ADD;
            break;
    }
}

void WaterGraphicsComponent::update(GameObject* obj) {
    m_bg_rects[0]->setRectX(obj->getPosX());
    m_bg_rects[1]->setRectX(obj->getPosX() > 0 ? obj->getPosX() - 640 : obj->getPosX() + 640);
    m_fg_rects[0]->setRectY(obj->getPosY());
    m_fg_rects[1]->setRectY(obj->getPosY() > 0 ? obj->getPosY() - 480 : obj->getPosY() + 480);
    
    for(auto r : m_fg_rects) SDL_SetTextureBlendMode(r->getTexture(), mFG_blendMode);
    for(auto r : m_bg_rects) {
        //SDL_SetTextureBlendMode(r->getTexture(), SDL_BLENDMODE_NONE);
        r->render(mRenderer);
    }
   
    for(auto r : m_fg_rects) {
        //SDL_SetTextureBlendMode(r->getTexture(), mFG_blendMode);
        r->render(mRenderer);
    }
}

WaterEffect::WaterEffect(SDL_Renderer* renderer,const std::string& name) {
    std::shared_ptr<TexturedRectangle> rect1 = std::make_shared<TexturedRectangle>(renderer, name.c_str());
    std::shared_ptr<TexturedRectangle> rect2 = std::make_shared<TexturedRectangle>(renderer, name.c_str());
    std::shared_ptr<TexturedRectangle> rect3 = std::make_shared<TexturedRectangle>(renderer, name.c_str());
    std::shared_ptr<TexturedRectangle> rect4 = std::make_shared<TexturedRectangle>(renderer, name.c_str());

    rect1->setRectangeProperties(0, 0, 640, 480);
    rect2->setRectangeProperties(-639, 0, 640, 480);

    rect3->setRectangeProperties(0, 0, 640, 480);
    rect4->setRectangeProperties(0,-480, 640, 480);
 
    m_bg_rects.push_back(rect1);
    m_bg_rects.push_back(rect2);
    
    m_fg_rects.push_back(rect3);
    m_fg_rects.push_back(rect4);
}

WaterEffect::~WaterEffect() {
}

void WaterEffect::update() {
    //texture moves left to right no blend mode
    for(auto r : m_bg_rects) {
        int temp = r->getRectX();
        temp++;
        if(temp > 639) temp = -639;
        r->setRectX(temp);
    }
    //texture2 moves top to down on top of texture, blends with different mode
    for(auto r : m_fg_rects) {
        int temp = r->getRectY();
        temp++;
        if(temp > 479) temp = -480;
        r->setRectY(temp);
    }
}

void WaterEffect::render(SDL_Renderer* renderer) {
    for(auto r : m_bg_rects) r->render(renderer);
    for(auto r : m_fg_rects) r->render(renderer);
}

void WaterEffect::setBlendMode(SDL_BlendMode blendMode) {
    for(auto r : m_fg_rects)
        SDL_SetTextureBlendMode(r->getTexture(), blendMode);
}

