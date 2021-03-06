#include "Collider.h"

#include <Windows.h>
#include <xnamath.h>

#include "GameObject.h"
#include "Transform.h"
#include "PhysicsManager.h"


Collider::~Collider() {
	physicsMgr->RemoveObject(go);
}

bool Collider::Init(GameObject* go) {
	this->go = go;
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
	auto distVector = XMVector3LengthSq(vectorDiff);
	float dist;
	XMStoreFloat(&dist, distVector);
	float radSq = transform->scale.x * transform->scale.x*.56 + otherTransform->scale.x * otherTransform->scale.x*.56;
	return dist <= radSq;
}