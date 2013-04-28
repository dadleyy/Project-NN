#include "Bullet.h"

#include <random>
using namespace std;

#include "ResourceManager.h"
#include "Drawable.h"
#include "BulletFiring.h"
#include "Transform.h"
#include "PrintUponCollision.h"
#include "Collider.h"


Bullet::Bullet(float xPos, float yPos, float zPos, XMFLOAT3 gForward) {
	transform = new Transform();
	sphere = new Drawable();
	print = new PrintUponCollision();
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
	//components.push_back(collider);
	components.push_back(transform);
	GameObject::InitComponents();
}

Bullet::~Bullet() {
	delete transform;
	delete sphere;
	delete collider;
	delete print;
}

void Bullet::Update(float dt){
	transform->position = XMFLOAT3( transform->position.x + (SPEED*forward.x)*dt,
	                     transform->position.y + (SPEED*forward.y)*dt,
	                     transform->position.z + (SPEED*forward.z)*dt);
	for(auto it = components.begin(); it != components.end(); ++it) {
		(*it)->Update(dt);
	}
}


void Bullet::Draw() {
	sphere->setEffectVariables();
	sphere->setEffectTextures();
	sphere->draw();
}