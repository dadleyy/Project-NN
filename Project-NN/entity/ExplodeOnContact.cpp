#include "ExplodeOnContact.h"

#include <iostream>
#include <unordered_set>

#include "GameObject.h"
#include "SceneManager.h"

ExplodeOnContact::ExplodeOnContact(float power) {
	this->power = power;
}

bool ExplodeOnContact::Init(GameObject* go) {
	this->go = go;
	return true;
}

void ExplodeOnContact::HandleCollision(GameObject* other) {
	//TODO: Explode
	go->active = false;
	//sceneMgr->Remove(go);
}