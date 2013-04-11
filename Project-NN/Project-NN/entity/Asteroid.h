#pragma once

#include "GameObject.h"

class Drawable;
class Wobble;
class Transform;
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
	Transform* transform;
};