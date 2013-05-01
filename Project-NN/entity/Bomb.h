#pragma once

#include "GameObject.h"

class Transform;
class Drawable;
class Collider;
class ExplodeOnContact;

class Bomb : public GameObject {
public:
	Bomb(float xPos, float yPos, float zPos);
	void Draw();

private:
	Transform* transform;
	Drawable* drawable;
	Collider* collider;
	ExplodeOnContact* explodeOnContact;
};