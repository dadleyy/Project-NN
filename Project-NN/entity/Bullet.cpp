#include "Bullet.h"

#include <random>
using namespace std;

#include "ResourceManager.h"
#include "Drawable.h"
#include "Transform.h"
#include "PrintUponCollision.h"
#include "Collider.h"


Bullet::Bullet(float xPos, float yPos, float zPos) {
	transform = new Transform();
	sphere = new Drawable();
	print = new PrintUponCollision();
	//collider = new Collider();

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
	//components.push_back(collider);
	components.push_back(transform);
	GameObject::InitComponents();
}

Bullet::~Bullet() {
	sphere->destroy();
	delete transform;
	delete sphere;
	delete collider;
	delete print;
}

void Bullet::Draw() {
	sphere->setEffectVariables();
	sphere->setEffectTextures();
	sphere->draw();
}