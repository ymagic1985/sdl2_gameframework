#pragma once

#include <string>
#include <SDL2/SDL.h>

namespace Man520 {

    class GameObject;
    class Component {
        public:
            virtual ~Component() {}
            virtual void receive(int message) = 0; //placeholer for messages, implement event queue to replace the int message here
    };

    class InputComponent : public Component {
        public:
            virtual ~InputComponent() {}
            virtual void receive(int message) override {}
            virtual void update(GameObject* obj) = 0;
    };

    class PhysicsComponent : public Component {
        public:
            virtual ~PhysicsComponent() {}
            virtual void receive(int message) override {};
            virtual void update(Uint32 dt, GameObject* obj) = 0;
    };

    class GraphicsComponent : public Component {
        public:
            virtual ~GraphicsComponent() {}
            virtual void receive(int message) override {};
            virtual void update(GameObject* obj) = 0;
    };
    
    class TagComponent : public Component {
        public:
            void receive(int message) override {}
            std::string mTag;
     };
}
