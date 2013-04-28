#include "SceneManager.h"

#include "entity/GameObject.h"


void SceneManager::Insert(GameObject* go) {
	inserted.push(go);
}

void SceneManager::Remove(GameObject* go) {
	go->active = false;
	deleted.push(go);
}

void SceneManager::Process() {
	while(!inserted.empty()) {
		sceneObjects.insert(inserted.front());
		inserted.pop();
	}
	while(!deleted.empty()) {
		sceneObjects.erase(deleted.front());
		delete deleted.front();
		deleted.pop();
	}
}

std::unordered_set<GameObject*>::iterator SceneManager::Begin() {
	return sceneObjects.begin();
}
std::unordered_set<GameObject*>::iterator SceneManager::End() {
	return sceneObjects.end();
}