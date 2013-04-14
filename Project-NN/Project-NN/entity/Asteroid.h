#pragma once

#include "GameObject.h"

class BoundingVolume;
class Drawable;
class PrintUponCollision;
class Transform;
class Wobble;
//TODO: Remove -- we have this in resourceMgr
struct ID3D11Device;
struct ID3D11DeviceContext;

class Asteroid : public GameObject {
public:
	Asteroid(ID3D11Device* device, ID3D11DeviceContext* immediateContext, float xPos, float yPos, float zPos);
	virtual ~Asteroid();
	void Draw();
private:
	Drawable* sphere;
	Wobble* wobble;
	BoundingVolume* bv;
	PrintUponCollision* print;
	Transform* transform;
};