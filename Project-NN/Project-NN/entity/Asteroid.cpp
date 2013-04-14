#include "Asteroid.h"

#include <random>
using namespace std;

#include "ResourceManager.h"
#include "Drawable.h"
#include "Wobble.h"
#include "Transform.h"
#include "PrintUponCollision.h"
#include "BoundingVolume.h"


Asteroid::Asteroid(ID3D11Device* device, ID3D11DeviceContext* immediateContext, float xPos, float yPos, float zPos) {
	transform = new Transform();
	wobble = new Wobble();
	sphere = new Drawable(device, immediateContext);
	print = new PrintUponCollision();
	bv = new BoundingVolume();

	transform->position = XMFLOAT3(xPos, yPos, zPos);
	transform->rotation = XMFLOAT4(0.707f, 0, 0, 0.707f);
	
	uniform_real_distribution<float> distribution(0.5f, 3.0f);
	float scale = distribution(resourceMgr->randomEngine);
	transform->scale = XMFLOAT3(scale, scale, scale);

    sphere->getEffectVariables("betterPhong", "Render");
	sphere->createBuffer("Sphere");
	sphere->addTexture("Test", "diffuseMap");

	components.push_back(sphere);
	components.push_back(print);
	components.push_back(wobble);
	components.push_back(bv);
	components.push_back(transform);
	GameObject::InitComponents();
}

Asteroid::~Asteroid() {
	sphere->destroy();
	delete transform;
	delete sphere;
	delete wobble;
	delete print;
}

void Asteroid::Draw() {
	sphere->draw();
}