#include "Bullet.h"

#include <random>
using namespace std;

#include "ResourceManager.h"
#include "Drawables/DrawLasers.h"
#include "BulletFiring.h"
#include "Transform.h"
#include "PrintUponCollision.h"
#include "Collider.h"
#include "BulletManager.h"
#include "PhysicsComponent.h"

Bullet::Bullet(BulletManager* gManager) : SPEED(20)
{
	transform = new Transform();

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
	
	components.push_back(print);
	components.push_back(fireBullet);
	components.push_back(collider);
	components.push_back(transform);
	manager->bullets.push_back(this);
	GameObject::InitComponents();
}

Bullet::Bullet(float xPos, float yPos, float zPos, XMFLOAT3 gForward): SPEED(20) 
{
	transform = new Transform();
	print = new PrintUponCollision();
	fireBullet = new BulletFiring();
	forward = gForward;
	collider = new Collider();

	transform->position = XMFLOAT3(xPos, yPos, zPos);
	transform->rotation = XMFLOAT4(0.707f, 0, 0, 0.707f);
	
	uniform_real_distribution<float> distribution(0.5f, 3.0f);
	float scale = 0.25;
	transform->scale = XMFLOAT3(scale, scale, scale);

	components.push_back(print);
	components.push_back(fireBullet);
	components.push_back(collider);
	components.push_back(transform);
	GameObject::InitComponents();
}

void Bullet::Draw() 
{
	laserDraw->points.push_back(transform->position);
	laserDraw->points.push_back(XMFLOAT3(transform->position.x + 2*forward.x, transform->position.y + 2*forward.y,transform->position.z + 2*forward.z));
}