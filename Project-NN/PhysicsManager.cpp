#include "PhysicsManager.h"

#include <algorithm>
using namespace std;

#include "entity/Collider.h"
#include "entity/GameObject.h"


void PhysicsManager::AddObject(GameObject* go) {
	if(go->collider == nullptr)
		return;
	inserted.insert(go);
}

void PhysicsManager::RemoveObject(GameObject* go) {
	deleted.insert(go);
}

void PhysicsManager::CheckForCollisions() {
	int initialLength = objects.size();
	for(auto it = objects.begin(); it != objects.end(); ++it) {
		auto collider1 = (*it)->collider;
		for(auto otherIt = it; otherIt != objects.end(); ++otherIt) {
			if(!(*it)->active || deleted.find(*it) != deleted.end())
				goto no_longer_active;
			if(it == otherIt || !(*otherIt)->active || deleted.find(*otherIt) != deleted.end())
				continue;
			if(initialLength != objects.size())
				DebugBreak();
			if(collider1->IsColliding(*otherIt)) {
				(*it)->HandleCollision(*otherIt);
				(*otherIt)->HandleCollision(*it);
			}
		}
		no_longer_active:;
	}
}

std::vector<GameObject*>::iterator PhysicsManager::Begin() {
	return objects.begin();
}

std::vector<GameObject*>::iterator PhysicsManager::End() {
	return objects.end();
}

void PhysicsManager::Process() {
	for(auto it = inserted.begin(); it != inserted.end(); ++it) {
		objects.push_back(*it);
	}
	inserted.clear();

	for(auto it = deleted.begin(); it != deleted.end(); ++it) {
		objects.erase(remove(objects.begin(), objects.end(), *it), objects.end());
	}
	deleted.clear();
}