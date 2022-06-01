#pragma once


#include "layer.h"
#include "sandboxScene.h"

class Sandbox2D : public Man520::Layer {
    public:
        Sandbox2D();
        virtual ~Sandbox2D();

        virtual void onAttach() override;
        virtual void onDetach() override;
        virtual void onUpdate() override;
        virtual void onEvent(SDL_Event& event) override;
    private:
        SandboxScene* mCurScene;        
};
