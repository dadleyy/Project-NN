#include "Asteroid.h"

#include "Drawable.h"
#include "Wobble.h"


Asteroid::Asteroid(ID3D11Device* device, ID3D11DeviceContext* immediateContext, float xPos, float yPos, float zPos) {
	wobble = new Wobble();
	sphere = new Drawable(device, immediateContext);
	sphere->setPosition(XMFLOAT3(xPos, yPos, zPos));
    sphere->getEffectVariables("sphereEffect", "Render");
	sphere->createBuffer("testSphere");
	components.push_back(sphere);
	components.push_back(wobble);
	GameObject::InitComponents();
}

Asteroid::~Asteroid() {
	sphere->destroy();
	delete sphere;
	delete wobble;
}

void Asteroid::Draw() {
	sphere->draw();
}