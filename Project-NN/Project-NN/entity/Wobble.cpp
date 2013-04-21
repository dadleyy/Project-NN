#include "Wobble.h"

#include <iostream>
#include <cmath>
#include <random>
using namespace std;

#include "ResourceManager.h"
#include "GameObject.h"
#include "Transform.h"


bool Wobble::Init(GameObject* go) {
	transform = go->GetComponent<Transform>();
	basePosition = transform->position;

	uniform_real_distribution<float> distribution(-1000, 1000);
	totalTime = distribution(resourceMgr->randomEngine);

	return transform != nullptr;
}

void Wobble::Update(float dt) {
	totalTime += dt;
	//TODO: We should accept the wobble amount and the speed as parameters.
	transform->position = XMFLOAT3(basePosition.x, basePosition.y + (sin(totalTime / 1.5f) * 0.4f), basePosition.z);
}