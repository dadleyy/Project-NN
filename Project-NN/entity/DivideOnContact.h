#pragma once

#include "Component.h"

class GameObject;

class DivideOnContact : public Component {
public:
	DivideOnContact(int divisionsRemaining);
	bool Init(GameObject* go);
	void HandleCollision(GameObject* other);

	int divisionsRemaining;

private:
	GameObject* go;
};