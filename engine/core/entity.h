#pragma once

#include "entt.hpp"
#include <cassert>

namespace Man520 {
    
    class Scene;

    class Entity {
    public:
        Entity() = default;
        Entity(entt::entity handle, Scene* scene);
        Entity(const Entity& rhs) = default;

        template<typename T, typename... Args>
        T& addComponent(Args&&... args) {
            //TODO:: assert if component has already been added
            assert(!this->hasComponent<T>());
            T& component = mScene->mRegistry.emplace<T>(mEntityHandle, std::forward<Args>(args)...);
            //mScene onComponentAdded Maybe
            return component;
        }

        template<typename T>
        T& getComponent() {
            assert(this->hasComponent<T>());
            return mScene->mRegistry.get<T>(mEntityHandle);
        }

        template<typename T>
        bool hasComponent() {
            return mScene->mRegistry.any_of<T>(mEntityHandle);
        }

        template<typename... T> 
        bool hasAllComponent() {
            return mScene->mRegistry.all_of<T...>(mEntityHandle);
        }

        template<typename T> 
        void removeComponent() {
            assert(this->hasComponent<T>());
            mScene->mRegistry.remove<T>(mEntityHandle);
        }

        bool isOrphan() const;

        operator bool() const { return mEntityHandle != entt::null; }
        operator entt::entity() const { return mEntityHandle; }
        operator uint32_t() const { return (uint32_t)mEntityHandle; }

        bool operator == (const Entity& rhs) const;
        bool operator != (const Entity& rhs) const;
    private:
        entt::entity mEntityHandle{ entt::null };
        Scene* mScene{ nullptr };
    };

}
