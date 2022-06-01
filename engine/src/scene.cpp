#include "scene.h"
#include "entity.h"

namespace Man520 {
    Scene::Scene() {
    }

    Scene::~Scene() {
    }

    Entity Scene::createEntity() {
        //mRegistry.emplace<entt::tag<name>>(e);
        Entity entity = { mRegistry.create(), this }; 
        //auto& tag = entity.addComponent<TagComponent>();
        //tag.mTag = name.empty() ? "Entity" : name;
        
        return entity;
    }

    void Scene::destroyEntity(Entity entity) {
        mRegistry.destroy(entity);
    }
}
