#include "gameObject.h"

GameObject::~GameObject() {
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

void GameObject::update(double dt) {
    if(mInput) mInput->update(this);
    if(mPhysics) mPhysics->update(dt, this);
    if(mGrapyhics) mGrapyhics->update();
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
