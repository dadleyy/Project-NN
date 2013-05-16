#pragma once

#include "Component.h"

class GameObject;
class Health;

class PlayerGameplay : public Component {
public:
	bool Init(GameObject* go);
	void Update(float dt);

private:
	Health* health;
};