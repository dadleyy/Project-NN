#pragma once

#include "GameObject.h"

class Collider;
class Drawable;
class PrintUponCollision;
class Transform;
class Wobble;
//TODO: Remove -- we have this in resourceMgr
struct ID3D11Device;
struct ID3D11DeviceContext;

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