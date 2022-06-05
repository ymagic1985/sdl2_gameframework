
#include "scene.h"
#include "entity.h"

namespace Man520 {

    Entity::Entity(entt::entity handle, Scene* scene) : mEntityHandle(handle), mScene(scene) {}
  
    bool Entity::isOrphan() const {
        return mScene->mRegistry.orphan(mEntityHandle);
    }

    bool Entity::operator == (const Entity& rhs) const {
        return mEntityHandle == rhs.mEntityHandle && mScene == rhs.mScene;
    }

    bool Entity::operator != (const Entity& rhs) const {
        return !(*this == rhs);
    }

}
