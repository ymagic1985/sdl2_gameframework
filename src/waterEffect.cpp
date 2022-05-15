#include <SDL2/SDL.h>
#include "waterEffect.h"
#include "texturedRectangle.h"

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
 
