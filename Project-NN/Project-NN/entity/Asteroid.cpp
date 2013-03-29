#include "Asteroid.h"

#include "Wobble.h"
#include "Sphere.h"

Asteroid::Asteroid(ID3D11Device* device, ID3D11DeviceContext* immediateContext) {
	wobble = new Wobble();
	sphere = new Sphere(device, immediateContext);
    sphere->getEffectVariables("sphereEffect", "Render");
	sphere->createBuffer();
	components.push_back(sphere);
	components.push_back(wobble);
	//TODO: This might be better off in GameObject.
	sphere->Init(this);
	wobble->Init(this);
}

Asteroid::~Asteroid() {
	sphere->destroy();
}

void Asteroid::Draw() {
	sphere->draw();
}