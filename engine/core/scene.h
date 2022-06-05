#pragma once

#include <entt.hpp>

namespace Man520 {
    
    class Entity;

    class Scene {
    public:
        Scene();
        virtual ~Scene();

        Entity createEntity();
        void destroyEntity(Entity entity);
        virtual void update() = 0;
    protected:
        entt::registry mRegistry;
        uint32_t mViewportWidth{0}, mViewportHeight{0};
    
    friend class Entity;
    };

}
            
