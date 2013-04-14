#include "PhysicsManager.h"

#include <algorithm>
using namespace std;

#include "entity/GameObject.h"

void PhysicsManager::AddObject(GameObject* go) {
	//TODO: Check if gameobject is in vector before adding it.
	objects.push_back(go);
}

void PhysicsManager::RemoveObject(GameObject* go) {
	objects.erase(remove(objects.begin(), objects.end(), go));
}

vector<GameObject*>::iterator PhysicsManager::Begin() {
	return objects.begin();
}

vector<GameObject*>::iterator PhysicsManager::End() {
	return objects.end();
}