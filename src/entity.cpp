
#include "scene.h"
#include "entity.h"

namespace Man520 {

    Entity::Entity(entt::entity handle, Scene* scene) : mEntityHandle(handle), mScene(scene) {}

    template<typename T, typename... Args>
    T& Entity::addComponent(Args&&... args) {
        //TODO: handle asset if component has already been added
        static_assert(hasComponent<T>(), "Component has already been added!");
        T& component = mScene->mRegistry.emplace<T>(mEntityHandle, std::forward<Args>(args)...);
        //mScene onComponentAdded Maybe
        return component;
    }

    template<typename T>
    T& Entity::getComponent() {
        //TODO: handle if entity doesn't have component
        return mScene->mRegistry.get<T>(mEntityHandle);
    }

    template<typename T>
    bool Entity::hasComponent() {
        return mScene->mRegistry.any_of<T>(mEntityHandle);
    }
    
    template<typename... T> 
    bool Entity::hasAllComponent() {
        return mScene->mRegistry.all_of<T...>(mEntityHandle);
    }

    template<typename T> 
    void Entity::removeComponent() {
        //TODO: handle if entity doesn't have component
        mScene->mRegistry.remove<T>(mEntityHandle);
    }
    
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
