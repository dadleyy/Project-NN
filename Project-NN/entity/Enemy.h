#pragma once

#include "GameObject.h"
#include "framework\MathHelper.h"

class Transform;
class Drawable;
class PhysicsComponent;
class AIComponent;

class Enemy : public GameObject {
public:
	Enemy(GameObject* initialTarget, XMFLOAT3 intialPosition );
	void Draw();

private:
	Transform* transform;
	Drawable* drawable;
	AIComponent* ai;
	PhysicsComponent* physics;
};

