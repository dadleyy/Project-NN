#include "BulletFiring.h"

#include <Windows.h>
#include <xnamath.h>

#include "GameObject.h"
#include "Transform.h"
#include "PhysicsManager.h"


BulletFiring::~BulletFiring() {
	physicsMgr->RemoveObject(go);
}

bool BulletFiring::Init(GameObject* go, XMFLOAT3* forward, int speed) {
	this->go = go;
	this->speed = speed;
	this->forward = forward;
	transform = go->GetComponent<Transform>();
	physicsMgr->AddObject(go);
	return transform != nullptr;
}

void BulletFiring::Update(float dt) {
	transform->position = XMFLOAT3(transform->position.x + (speed*forward->x)*dt,
	                     transform->position.y + (speed*forward->y)*dt,
	                     transform->position.z + (speed*forward->z)*dt);
}
