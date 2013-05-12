#include "BulletFiring.h"

#include <Windows.h>
#include <xnamath.h>

#include "GameObject.h"
#include "Transform.h"
#include "PhysicsManager.h"
#include "Bullet.h";


bool BulletFiring::Init(GameObject* go) {
	this->go = go;
	this->speed = dynamic_cast<Bullet*>(go)->SPEED;
	//this->forward = dynamic_cast<Bullet*>(go)->forward;
	transform = go->GetComponent<Transform>();
	physicsMgr->AddObject(go);
	return transform != nullptr;
}

void BulletFiring::Update(float dt) {
	transform->position = XMFLOAT3(transform->position.x + (dynamic_cast<Bullet*>(go)->forward.x*speed)*dt,
	                     transform->position.y + (dynamic_cast<Bullet*>(go)->forward.y*speed)*dt,
	                     transform->position.z + (dynamic_cast<Bullet*>(go)->forward.z*speed)*dt);
}
