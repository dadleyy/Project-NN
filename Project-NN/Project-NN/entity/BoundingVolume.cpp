#include "BoundingVolume.h"

#include <Windows.h>
#include <xnamath.h>

#include "GameObject.h"
#include "Transform.h"
#include "PhysicsManager.h"

BoundingVolume::BoundingVolume() {
}

void BoundingVolume::Init(GameObject* go) {
	//TODO: Error checking
	transform = go->GetComponent<Transform>();
	physicsMgr->AddObject(go);
}

void BoundingVolume::Update(float dt) {
}

bool BoundingVolume::IsColliding(GameObject* other) {
	auto otherTransform = other->GetComponent<Transform>();
	auto v1 = XMLoadFloat3(&transform->position);
	auto v2 = XMLoadFloat3(&otherTransform->position);
	auto vectorDiff = XMVectorSubtract(v1, v2);
	auto distVector = XMVector3Length(vectorDiff);
	float dist;
	XMStoreFloat(&dist, distVector);
	return dist <= transform->scale.x + otherTransform->scale.x;
}