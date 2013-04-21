#pragma once

#include "GameObject.h"

class Collider;
class Drawable;
class PrintUponCollision;
class Transform;
class Wobble;


class Asteroid : public GameObject {
public:
	Asteroid(float xPos, float yPos, float zPos);
	virtual ~Asteroid();
	void Draw();
private:
	Drawable* sphere;
	Wobble* wobble;
	Collider* collider;
	PrintUponCollision* print;
	Transform* transform;
};