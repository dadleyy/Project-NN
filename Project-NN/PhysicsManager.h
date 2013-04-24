#pragma once

#include <vector>

class GameObject;


class PhysicsManager {
public:
	void AddObject(GameObject* go);
	void RemoveObject(GameObject* go);
	void CheckForCollisions();
	std::vector<GameObject*>::iterator Begin();
	std::vector<GameObject*>::iterator End();
private:
	std::vector<GameObject*> objects;
};

extern PhysicsManager* physicsMgr;