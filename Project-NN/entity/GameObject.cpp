#include "entity/GameObject.h"

#include <iostream>
#include <stdexcept>

#include "Component.h"
#include "Transform.h"
#include "Collider.h"


GameObject::GameObject() : active(false) {
}

GameObject::~GameObject() {
}

void GameObject::InitComponents() {
	for(auto it = components.begin(); it != components.end(); ++it) {
		bool successful = (*it)->Init(this);
		if(!successful) {
			std::cerr << "A component could not initialize properly! (" << (*it) << ")" << std::endl;
			exit(1);
		}
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

void GameObject::Draw() {
}

void GameObject::HandleCollision(GameObject* other) {
	for(auto it = components.begin(); it != components.end(); ++it) {
		(*it)->HandleCollision(other);
	}
}

GameObject* GameObject::Clone() {
	//If a subclass doesn't override this, it shouldn't be able to clone itself.
	throw std::runtime_error("GameObject::Clone must be overridden if you want to clone!");
	return nullptr;
}