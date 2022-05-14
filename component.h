
class Component {
    public:
        virtual ~Component() {}
        virtual void receive(int message) = 0; //placeholer for messages, implement event queue to replace the int message here
};

class InputComponent : public Component {
    Public:
        virtual ~InputComponent() {};
        virtual void receive(int message) override;
        virtual void update();
};

class PhysicsComponent : public Component {
    public:
        virtual ~PhysicsComponent() {};
        virtual void receive(int message) override;
        virtual void update(double dt);
};

class GraphicsComponent : public Component {
    public:
        virtual ~GraphicsComponent() {};
        virtual void receive(int message) override;
        virtual void update() override;
};


