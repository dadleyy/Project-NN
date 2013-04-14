#include "PhysicsManager.h"

#include <algorithm>
using namespace std;

#include "entity/BoundingVolume.h"
#include "entity/GameObject.h"


void PhysicsManager::AddObject(GameObject* go) {
	//TODO: Check if gameobject is in vector before adding it.
	//TODO: Ensure that the gameobject has the required components.
	objects.push_back(go);
}

void PhysicsManager::RemoveObject(GameObject* go) {
	objects.erase(remove(objects.begin(), objects.end(), go));
}

void PhysicsManager::CheckForCollisions() {
	for(auto it = objects.begin(); it != objects.end(); ++it) {
		auto collider1 = (*it)->GetComponent<BoundingVolume>();
		for(auto otherIt = it; otherIt != objects.end(); ++otherIt) {
			if(it == otherIt)
				continue;
			if(collider1->IsColliding(*otherIt)) {
				(*it)->HandleCollision(*otherIt);
				(*otherIt)->HandleCollision(*it);
			}
		}
	}
}