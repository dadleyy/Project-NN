#include "entity/GameObject.h"

#include "Component.h"


void GameObject::InitComponents() {
	for(auto it = components.begin(); it != components.end(); ++it) {
		(*it)->Init(this);
	}
}

void GameObject::Update(float dt) {
	for(auto it = components.begin(); it != components.end(); ++it) {
		(*it)->Update(dt);
	}
}

void GameObject::HandleCollision(GameObject* other) {
	for(auto it = components.begin(); it != components.end(); ++it) {
		(*it)->HandleCollision(other);
	}
}