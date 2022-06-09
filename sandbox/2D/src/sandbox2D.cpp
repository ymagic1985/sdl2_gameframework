
#include "sandbox2D.h"

Sandbox2D::Sandbox2D() : mCurScene(nullptr) {
}

Sandbox2D::~Sandbox2D() {
    
}

void Sandbox2D::onAttach() {
    mCurScene = new SandboxScene();
}

void Sandbox2D::onDetach() {
    delete mCurScene;
}

void Sandbox2D::onUpdate() {
    mCurScene->update();
}

void Sandbox2D::onEvent(SDL_Event& event) {
        
}


