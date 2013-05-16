#pragma once

#include "Component.h"

class Health : public Component {
public:
	Health(int hp);
	void Damage(int hp);
	void Heal(int hp);
	bool IsAlive();
	void HandleCollision(GameObject* other);
private:
	int hp;
};