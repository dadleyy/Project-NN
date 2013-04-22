#include "Asteroid.h"

#include <random>
using namespace std;

#include "ResourceManager.h"
#include "Drawable.h"
#include "Wobble.h"
#include "Transform.h"
#include "PrintUponCollision.h"
#include "Collider.h"


Asteroid::Asteroid(float xPos, float yPos, float zPos) {
	transform = new Transform();
	wobble = new Wobble();
	sphere = new Drawable();
	print = new PrintUponCollision();
	collider = new Collider();

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
	components.push_back(collider);
	components.push_back(transform);
	GameObject::InitComponents();
}

void Asteroid::fillInstanceData(vector<XMFLOAT4X4>* data)
{
	//translate, rotate, and scale matrix
	XMMATRIX translate = XMMatrixTranslation(transform->position.x, transform->position.y, transform->position.z);
	XMMATRIX rotation = XMMatrixRotationQuaternion(XMLoadFloat4(&transform->rotation));
	XMMATRIX scale = XMMatrixScaling(transform->scale.x, transform->scale.y, transform->scale.z);
	XMMATRIX w = scale * rotation * translate;

	XMFLOAT4X4 stupid;
	XMFLOAT4X4 pieceOfshit;
	XMStoreFloat4x4(&stupid, w);
	XMStoreFloat4x4(&pieceOfshit, rotation);

	data->push_back(stupid); 
	data->push_back(pieceOfshit);
}

Asteroid::~Asteroid() {
	delete transform;
	delete sphere;
	delete collider;
	delete wobble;
	delete print;
}

void Asteroid::Draw() {
	sphere->setEffectVariables();
	sphere->setEffectTextures();
	sphere->draw();
}