#pragma once

#include "Component.h"

class GameObject;

class DivideOnContact : public Component {
public:
	DivideOnContact(int minimumScale);
	bool Init(GameObject* go);
	void HandleCollision(GameObject* other);

	int minScale;

private:
	GameObject* go;
};