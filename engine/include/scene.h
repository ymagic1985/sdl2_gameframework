#pragma once

#include "entt.hpp"

namespace Man520 {
    
    class Entity;

    class Scene {
    public:
        Scene();
        ~Scene();

        Entity createEntity();
        void destroyEntity(Entity entity);
        void update();
    private:
        entt::registry mRegistry;
        uint32_t mViewportWidth{0}, mViewportHeight{0};
    
    friend class Entity;
    };

}
            
