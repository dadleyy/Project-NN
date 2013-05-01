#include "Asteroid.h"

#include <algorithm>
#include <random>
using namespace std;

#include "ResourceManager.h"
#include "Drawable.h"
#include "Wobble.h"
#include "Transform.h"
#include "DivideOnContact.h"
#include "Collider.h"
#include "Health.h"
#include "PhysicsComponent.h"

Asteroid::Asteroid(float xPos, float yPos, float zPos, vector<Asteroid*>* asteroids) {
	transform = new Transform();
	collider = new Collider();
	divide = new DivideOnContact(3);

	this->asteroids = asteroids;

	transform->position = XMFLOAT3(xPos, yPos, zPos);
	//TODO: set randomly
	transform->rotation = XMFLOAT4(0.707f, 0, 0, 0.707f);
	
	//TODO: accept as a parameter
	uniform_real_distribution<float> distribution(1.0f, 13.0f);
	float scale = distribution(resourceMgr->randomEngine);
	transform->scale = XMFLOAT3(scale, scale, scale);
	PhysicsComponent* physics = new PhysicsComponent(XMFLOAT3(0,0,1), XMFLOAT3(1,0,0), XMFLOAT3(0,1,0), 100*scale, 0, 20, transform->position, XMFLOAT3(0,0,0), XMFLOAT3(0,0,0), 0, 0);
	physics->accelerationDamp = 0;
	physics->velocityDamp = 0;


	components.push_back(divide);
	components.push_back(collider);
	components.push_back(transform);
	components.push_back(physics);
	components.push_back(new Health(100));
	GameObject::InitComponents();

}

void Asteroid::fillInstanceData(vector<XMFLOAT4X4>* data)
{
	//translate, rotate, and scale matrix
	XMMATRIX translate = XMMatrixTranslation(transform->position.x, transform->position.y, transform->position.z);
	XMMATRIX rotation = XMMatrixRotationQuaternion(XMLoadFloat4(&transform->rotation));
	XMMATRIX scale = XMMatrixScaling(transform->scale.x, transform->scale.y, transform->scale.z);
	XMMATRIX w = scale * rotation * translate;

	XMFLOAT4X4 world;
	XMFLOAT4X4 normalWorld;
	XMStoreFloat4x4(&world, w);
	XMStoreFloat4x4(&normalWorld, rotation);

	data->push_back(world); 
	data->push_back(normalWorld);
}

GameObject* Asteroid::Clone() {
	auto asteroid = new Asteroid(transform->position.x, transform->position.y, transform->position.z, asteroids);
	asteroid->transform->rotation = transform->rotation;
	asteroid->transform->scale = transform->scale;
	asteroids->push_back(asteroid);
	return asteroid;
}

Asteroid::~Asteroid() {
	asteroids->erase(std::remove(asteroids->begin(), asteroids->end(), this), asteroids->end());
}
