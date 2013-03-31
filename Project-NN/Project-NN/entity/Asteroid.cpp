#include "Asteroid.h"




Asteroid::Asteroid(ID3D11Device* device, ID3D11DeviceContext* immediateContext) {
	wobble = new Wobble();
	sphere = new Drawable(device, immediateContext);
    sphere->getEffectVariables("sphereEffect", "Render");
	sphere->createBuffer("testSphere");
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