#include "entity/GameObject.h"

#include <iostream>
#include <typeinfo>
using namespace std;

#include "Component.h"

void GameObject::Update(float dt) {
	for(auto it = components.begin(); it != components.end(); ++it) {
		(*it)->Update(dt);
	}
}
