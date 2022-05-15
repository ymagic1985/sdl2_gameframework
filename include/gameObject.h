
#include <vector>
#include "component.h"

struct Vector2D {
    float x;
    float y;
};

typedef Vector2D Point2D;

class GameObject {
    public:
        GameObject(){}
        GameObject(InputComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics) :
            mInput(input), mPhysics(physics), mGrapyhics(graphics) {}
        virtual ~GameObject();
        GameObject(const GameObject& rhs);
        GameObject& operator=(const GameObject& rhs);
        GameObject(GameObject&& rhs);        
        GameObject& operator=(GameObject&& rhs);
        
        virtual void update(double dt);
        void setPosX(float posX);
        void setPosY(float posY);
        void setPosition(Point2D pos);
        inline float getPosX() const { return mPosition.x; }
        inline float getPosY() const { return mPosition.y; }
        inline Point2D getPosition() const { return mPosition; }

    protected:
        Point2D mPosition;
        InputComponent* mInput;
        PhysicsComponent* mPhysics;
        GraphicsComponent* mGrapyhics;
        std::vector<Component*> mComponents;
};
