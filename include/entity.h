#pragma once

#include "entt.hpp"

namespace Man520 {
    
    class Scene;

    class Entity {
    public:
        Entity() = default;
        Entity(entt::entity handle, Scene* scene);
        Entity(const Entity& rhs) = default;

        template<typename T, typename... Args>
        T& addComponent(Args&&... args);
        template<typename T>
        T& getComponent();
        template<typename T>
        bool hasComponent();
        template<typename... T> 
        bool hasAllComponent();
        template<typename T> 
        void removeComponent();
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
