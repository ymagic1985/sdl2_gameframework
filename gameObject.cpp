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

void GameObject::Jump() {
}

void GameObject::Fire() {
}
