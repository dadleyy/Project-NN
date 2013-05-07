#include "Bullet.h"

#include <random>
using namespace std;

#include "ResourceManager.h"
#include "Drawable.h"
#include "BulletFiring.h"
#include "Transform.h"
#include "PrintUponCollision.h"
#include "Collider.h"
#include "BulletManager.h"

Bullet::Bullet(BulletManager* gManager) {
	transform = new Transform();
	sphere = new Drawable();
	print = new PrintUponCollision();
	fireBullet = new BulletFiring();
	forward = XMFLOAT3();
	
	collider = new Collider();
	manager = gManager;

	transform->position = XMFLOAT3(0,0,0);
	transform->rotation = XMFLOAT4(0.707f, 0, 0, 0.707f);
	
	uniform_real_distribution<float> distribution(0.5f, 3.0f);
	float scale = 1;
	transform->scale = XMFLOAT3(scale, scale, scale);

	active = false;

    sphere->getEffectVariables("betterPhong", "Render");
	sphere->setShader("betterPhong", "Render");
	sphere->createBuffer("Sphere");
	sphere->addTexture("Test2", "diffuseMap");
	
	components.push_back(sphere);
	components.push_back(print);
	components.push_back(fireBullet);
	components.push_back(collider);
	components.push_back(transform);
	manager->bullets.push_back(this);
	GameObject::InitComponents();
}

Bullet::Bullet(float xPos, float yPos, float zPos, XMFLOAT3 gForward) {
	transform = new Transform();
	sphere = new Drawable();
	print = new PrintUponCollision();
	fireBullet = new BulletFiring();
	forward = gForward;
	//collider = new Collider();

	transform->position = XMFLOAT3(xPos, yPos, zPos);
	transform->rotation = XMFLOAT4(0.707f, 0, 0, 0.707f);
	
	uniform_real_distribution<float> distribution(0.5f, 3.0f);
	float scale = 0.25;
	transform->scale = XMFLOAT3(scale, scale, scale);

    sphere->getEffectVariables("betterPhong", "Render");
	sphere->createBuffer("Sphere");
	sphere->addTexture("Test", "diffuseMap");

	components.push_back(sphere);
	components.push_back(print);
	components.push_back(fireBullet);
	//components.push_back(collider);
	components.push_back(transform);
	GameObject::InitComponents();
}

void Bullet::Draw() {
	sphere->setEffectVariables();
	sphere->setEffectTextures();
	sphere->draw();
}