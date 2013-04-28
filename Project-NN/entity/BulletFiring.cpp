#include "BulletFiring.h"

#include <Windows.h>
#include <xnamath.h>

#include "GameObject.h"
#include "Transform.h"
#include "PhysicsManager.h"


BulletFiring::~BulletFiring() {
	physicsMgr->RemoveObject(go);
}

bool BulletFiring::Init(GameObject* go, XMFLOAT3* forward) {
	this->go = go;
	this->forward = forward;
	transform = go->GetComponent<Transform>();
	physicsMgr->AddObject(go);
	return transform != nullptr;
}

void BulletFiring::Update(float dt) {
}
