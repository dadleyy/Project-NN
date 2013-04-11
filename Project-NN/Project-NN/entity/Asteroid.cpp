#include "Asteroid.h"

#include <random>
using namespace std;

#include "ResourceManager.h"
#include "Drawable.h"
#include "Wobble.h"
#include "Transform.h"

extern ResourceManager* drawAtts;

Asteroid::Asteroid(ID3D11Device* device, ID3D11DeviceContext* immediateContext, float xPos, float yPos, float zPos) {
	transform = new Transform();
	wobble = new Wobble();
	sphere = new Drawable(device, immediateContext);
	transform->position = XMFLOAT3(xPos, yPos, zPos);
	
	uniform_real_distribution<float> distribution(0.5f, 3.0f);
	float scale = distribution(drawAtts->randomEngine);
	transform->scale = XMFLOAT3(scale, scale, scale);

	transform->rotation = XMFLOAT4(0.707f, 0, 0, 0.707f);

    sphere->getEffectVariables("betterPhong", "Render");
	sphere->createBuffer("Sphere");
	sphere->addTexture("Test", "diffuseMap");
	components.push_back(sphere);
	components.push_back(wobble);
	components.push_back(transform);
	GameObject::InitComponents();
}

Asteroid::~Asteroid() {
	sphere->destroy();
	delete transform;
	delete sphere;
	delete wobble;
}

void Asteroid::Draw() {
	sphere->draw();
}