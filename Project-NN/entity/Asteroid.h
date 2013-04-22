#pragma once

#include "GameObject.h"

using std::vector;

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
	void fillInstanceData(vector<XMFLOAT4X4>* data);
private:
	Drawable* sphere;
	Wobble* wobble;
	Collider* collider;
	PrintUponCollision* print;
	Transform* transform;
};