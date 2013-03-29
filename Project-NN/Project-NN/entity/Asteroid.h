#pragma once

#include "GameObject.h"

class Sphere;
class Wobble;
struct ID3D11Device;
struct ID3D11DeviceContext;

class Asteroid : public GameObject {
public:
	Asteroid(ID3D11Device* device, ID3D11DeviceContext* immediateContext);
	virtual ~Asteroid();

	void Draw();
private:
	Sphere* sphere;
	Wobble* wobble;
};