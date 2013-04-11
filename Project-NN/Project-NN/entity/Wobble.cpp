#include "Wobble.h"

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <random>
using namespace std;

#include "ResourceManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "Drawable.h"


extern ResourceManager* drawAtts;

Wobble::~Wobble() {
	delete transform;
	delete drawable;
}

void Wobble::Init(GameObject* go) {
	drawable = go->GetComponent<Drawable>();
	transform = go->GetComponent<Transform>();
	if(drawable == nullptr) {
		cerr << "ERROR: Drawable not found!" << endl;
		exit(1);
	}
	if(transform == nullptr) {
		cerr << "ERROR: Transform not found!" << endl;
		exit(1);
	}
	basePosition = transform->position;

	uniform_real_distribution<float> distribution(-1000, 1000);
	totalTime = distribution(drawAtts->randomEngine);
}

void Wobble::Update(float dt) {
	totalTime += dt;
	//TODO: We should accept the wobble amount and the speed as parameters.
	transform->position = XMFLOAT3(basePosition.x, basePosition.y + (sin(totalTime / 1.5f) * 0.4f), basePosition.z);
}