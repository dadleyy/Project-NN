#include "Wobble.h"

#include <iostream>
#include <cmath>
using namespace std;

#include "GameObject.h"
#include "Drawable.h"
#include "Sphere.h"


void Wobble::Init(GameObject* go) {
	drawable = go->GetComponent<Sphere>();
	if(drawable == nullptr) {
		//TODO: Cause program to crash
		cout << "ERROR: Drawable not found!" << endl;
		return;
	}
	basePosition = drawable->getPosition();
	totalTime = 0;
}

void Wobble::Update(float dt) {
	totalTime += dt;
	//TODO: We should accept the wobble amount and the speed as parameters.
	XMFLOAT3 newPosition = XMFLOAT3(basePosition.x, basePosition.y + (sin(totalTime / 1.5f) * 0.4f), basePosition.z);
	drawable->setPosition(newPosition);
}