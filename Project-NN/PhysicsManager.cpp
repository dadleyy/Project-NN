#include "PhysicsManager.h"

#include <algorithm>
using namespace std;

#include "entity/Collider.h"
#include "entity/GameObject.h"


void PhysicsManager::AddObject(GameObject* go) {
	if(go->collider == nullptr)
		return;
	objects.push_back(go);
}

void PhysicsManager::RemoveObject(GameObject* go) {
	objects.erase(remove(objects.begin(), objects.end(), go));
}

void PhysicsManager::CheckForCollisions() {
	for(auto it = objects.begin(); it != objects.end(); ++it) {
		if(!(*it)->active)
			continue;
		auto collider1 = (*it)->collider;
		for(auto otherIt = it; otherIt != objects.end(); ++otherIt) {
			if(it == otherIt || !(*otherIt)->active)
				continue;
			if(collider1->IsColliding(*otherIt)) {
				(*it)->HandleCollision(*otherIt);
				(*otherIt)->HandleCollision(*it);
			}
		}
	}
}

std::vector<GameObject*>::iterator PhysicsManager::Begin() {
	return objects.begin();
}

std::vector<GameObject*>::iterator PhysicsManager::End() {
	return objects.end();
}