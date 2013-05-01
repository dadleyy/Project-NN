#include "Component.h"
#include "GameObject.h"

Component::~Component() {
}

bool Component::Init(GameObject* go) {
	return true;
}

void Component::Update(float dt) {
}

void Component::HandleCollision(GameObject* other) {
}