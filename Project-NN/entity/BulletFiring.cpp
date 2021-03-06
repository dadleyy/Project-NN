#include "BulletFiring.h"

#include <Windows.h>
#include <xnamath.h>

#include "GameObject.h"
#include "Transform.h"
#include "PhysicsManager.h"
#include "Bullet.h"


bool BulletFiring::Init(GameObject* go) {
	this->go = go;
	this->speed = dynamic_cast<Bullet*>(go)->SPEED;
	transform = go->GetComponent<Transform>();
	return transform != nullptr;
}

void BulletFiring::Update(float dt) {
	transform->position = XMFLOAT3(transform->position.x + forward.x*speed*dt,
	                     transform->position.y + forward.y*speed*dt,
	                     transform->position.z + forward.z*speed*dt);
	time -=dt;
	if (time <= 0.0)
	{
		go->active = false;
	}
}

void BulletFiring::HandleCollision(GameObject* other) {
	//TODO: Explode
	go->active = false;
}


void BulletFiring::SetActive() {
	go->active = true;
	time = 10.0;
}
