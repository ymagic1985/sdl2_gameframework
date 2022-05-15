
#include <vector>
#include <memory>
#include <string>

#include <SDL2/SDL.h>

#include "component.h"

class WaterInputComponent : public InputComponent {
    public:
        virtual void receive(int message) override;
        virtual void update(GameObject* obj) override;
};

class TexturedRectangle;

class WaterEffect {
    public:
        WaterEffect(SDL_Renderer* renderer, const std::string& name);
        ~WaterEffect();
        void update();
        void render(SDL_Renderer* renderer);
        //testing purpose
        void setBlendMode(SDL_BlendMode blendMode);
    private:
        std::vector<std::shared_ptr<TexturedRectangle> > m_fg_rects;
        std::vector<std::shared_ptr<TexturedRectangle> > m_bg_rects;
};
