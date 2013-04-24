#include "ExplodeOnContact.h"

#include <iostream>
#include <unordered_set>

#include "GameObject.h"

extern std::unordered_set<GameObject*> sceneObjects;

ExplodeOnContact::ExplodeOnContact(float power) {
	this->power = power;
}

bool ExplodeOnContact::Init(GameObject* go) {
	this->go = go;
	return true;
}

void ExplodeOnContact::HandleCollision(GameObject* other) {
	//TODO: Explode
	sceneObjects.erase(go);
}