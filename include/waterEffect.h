
#include <vector>
#include <memory>
#include <string>

#include <SDL2/SDL.h>

#include "component.h"

class TexturedRectangle;

class WaterInputComponent : public InputComponent {
    public:
        virtual void receive(int message) override;
        virtual void update(GameObject* obj) override;
};

class WaterPyhsicsComponent : public PhysicsComponent {
    public:
        WaterPyhsicsComponent();
        ~WaterPyhsicsComponent(); 
        virtual void receive(int message) override;
        virtual void update(Uint32 dt, GameObject* obj) override;
    private:
        float mHori_velocity;
        float mVert_velocity;
};

class WaterGraphicsComponent : public GraphicsComponent {
    public:
        WaterGraphicsComponent(SDL_Renderer* renderer, const std::string& name);
        virtual void receive(int message) override;
        virtual void update(GameObject* obj) override;
    private:
        SDL_Renderer* mRenderer;
        SDL_BlendMode mFG_blendMode;
        std::vector<std::shared_ptr<TexturedRectangle> > m_fg_rects;
        std::vector<std::shared_ptr<TexturedRectangle> > m_bg_rects;
};

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
