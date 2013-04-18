#include "entity/GameObject.h"

#include "Component.h"
#include "Transform.h"
#include "Collider.h"


void GameObject::InitComponents() {
	for(auto it = components.begin(); it != components.end(); ++it) {
		(*it)->Init(this);
		//TODO: Refactor
		auto asTransform = dynamic_cast<Transform*>(*it);
		transform = asTransform == nullptr ? transform : asTransform;
		auto asCollider = dynamic_cast<Collider*>(*it);
		collider = asCollider == nullptr ? collider : asCollider;
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