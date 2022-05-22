#include "gameObject.h"

GameObject::GameObject(InputComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics) : mInput(input), mPhysics(physics), mGrapyhics(graphics) {
        mComponents.push_back(mInput);
        mComponents.push_back(mPhysics);
        mComponents.push_back(mGrapyhics);
        mPosition.x = 0.0f;
        mPosition.y = 0.0f;
 }

GameObject::~GameObject() {
   /* for(auto com : mComponents) {
        delete com;
    }
    mComponents.clear();*/
}

GameObject::GameObject(const GameObject& rhs) {
    this->operator=(rhs);
}

GameObject& GameObject::operator=(const GameObject& rhs) {
    if(this != &rhs) {
    }
    return *this;
}

GameObject::GameObject(GameObject&& rhs){
    this->operator=(rhs);
}

GameObject& GameObject::operator=(GameObject&& rhs) {
    if(this != &rhs) {
       //delete data in rhs
    }
    return *this;
}

void GameObject::update(Uint32 dt) {
    if(mInput) mInput->update(this);
    if(mPhysics) mPhysics->update(dt, this);
    if(mGrapyhics) mGrapyhics->update(this);
}

void GameObject::setPosX(float posX) {
    mPosition.x = posX;
}

void GameObject::setPosY(float posY) {
    mPosition.y = posY;
}

void GameObject::setPosition(Point2D pos) {
    mPosition = pos;
}

void GameObject::sendMessage(Component* sender, int message) {
    for(auto receiver : mComponents) {
        if(receiver != sender) {
            receiver->receive(message);
        }
    }
}
