#include "sandboxScene.h" 
#include "animatedSprite.h"
#include "entity.h"

SandboxScene::SandboxScene() {
    Man520::Entity player = createEntity();
    //entity.addComponent<Man520::AnimatedSprite>
}

SandboxScene::~SandboxScene() {
}

void SandboxScene::update() {
}
