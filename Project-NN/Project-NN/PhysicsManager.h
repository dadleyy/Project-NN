#pragma once

#include <vector>

class GameObject;


class PhysicsManager {
public:
	void AddObject(GameObject* go);
	void RemoveObject(GameObject* go);
	void CheckForCollisions();
private:
	std::vector<GameObject*> objects;
};

extern PhysicsManager* physicsMgr;