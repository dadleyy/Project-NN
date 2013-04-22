#include "ExplodeOnContact.h"

#include <iostream>

#include "GameObject.h"

ExplodeOnContact::ExplodeOnContact(float power) {
	this->power = power;
}

void ExplodeOnContact::HandleCollision(GameObject* other) {
	//TODO: Explode
}