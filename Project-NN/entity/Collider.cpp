#include "Collider.h"

#include <Windows.h>
#include <xnamath.h>

#include "GameObject.h"
#include "Transform.h"
#include "PhysicsManager.h"

Collider::Collider() {
}

bool Collider::Init(GameObject* go) {
	transform = go->GetComponent<Transform>();
	physicsMgr->AddObject(go);
	return transform != nullptr;
}

void Collider::Update(float dt) {
}

bool Collider::IsColliding(GameObject* other) {
	auto otherTransform = other->transform;
	auto v1 = XMLoadFloat3(&transform->position);
	auto v2 = XMLoadFloat3(&otherTransform->position);
	auto vectorDiff = XMVectorSubtract(v1, v2);
	auto distVector = XMVector3Length(vectorDiff);
	float dist;
	XMStoreFloat(&dist, distVector);
	return dist <= transform->scale.x + otherTransform->scale.x;
}