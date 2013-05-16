#include "DivideOnContact.h"
#include "PhysicsComponent.h"
#include "framework/quaternionMath.h"
#include "Health.h"
#include "GameObject.h"
#include "Transform.h"
#include "SceneManager.h"


DivideOnContact::DivideOnContact(int minimumScale) {
	minScale = minimumScale;
}

bool DivideOnContact::Init(GameObject* go) {
	this->go = go;
	return true;
}

void DivideOnContact::HandleCollision(GameObject* other) {
	//We want to make sure that it's the ship that's colliding.
	Health* health = go->GetComponent<Health>();
	if(!health) return;
	if(go->GetComponent<Health>()->IsAlive())
		return;

	if(go->transform->scale.x > minScale) {
		auto obj1 = go->Clone();
		auto obj2 = go->Clone();
		auto obj3 = go->Clone();

		float scaleDim = obj1->transform->scale.x;
		obj1->transform->position.x += scaleDim;
		obj1->transform->scale = scale(obj1->transform->scale, 0.7f);
		obj2->transform->position.x -= scaleDim;
		obj2->transform->scale = scale(obj2->transform->scale, 0.7f);
		obj3->transform->position.y -= scaleDim;
		obj3->transform->scale = scale(obj3->transform->scale, 0.7f);

		PhysicsComponent* physics = go->GetComponent<PhysicsComponent>();
		XMFLOAT3 initialVel = normalize(physics->velocity);
		float initialSpeed = physics->speed;

		physics = obj1->GetComponent<PhysicsComponent>();
		obj1->GetComponent<Health>()->setHealth(obj1->transform->scale.x*10);
		physics->velocity = scale(normalize(add(initialVel,XMFLOAT3(1,0,0))), initialSpeed*1.5);
		physics->rotAxis = normalize(XMFLOAT3(rand(), rand(), rand()));
		physics->angularVelocity = (((float)rand())/RAND_MAX) * 20;

		physics = obj2->GetComponent<PhysicsComponent>();
		obj2->GetComponent<Health>()->setHealth(obj2->transform->scale.x*10);
		physics->velocity = scale(normalize(add(initialVel,XMFLOAT3(-1,0,0))), initialSpeed*1.5);
		physics->rotAxis = normalize(XMFLOAT3(rand(), rand(), rand()));
		physics->angularVelocity = (((float)rand())/RAND_MAX) * 20;

		physics = obj3->GetComponent<PhysicsComponent>();
		obj3->GetComponent<Health>()->setHealth(obj3->transform->scale.x*10);
		physics->velocity = scale(normalize(add(initialVel,XMFLOAT3(0,-1,0))), initialSpeed*1.5);
		physics->rotAxis = normalize(XMFLOAT3(rand(), rand(), rand()));
		physics->angularVelocity = (((float)rand())/RAND_MAX) * 20;

		sceneMgr->Insert(obj1);
		sceneMgr->Insert(obj2);
		sceneMgr->Insert(obj3);
	}

	sceneMgr->Remove(go);
}