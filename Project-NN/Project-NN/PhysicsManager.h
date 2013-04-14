#pragma once

#include <vector>

class GameObject;


class PhysicsManager {
public:
	void AddObject(GameObject* go);
	void RemoveObject(GameObject* go);
	std::vector<GameObject*>::iterator Begin();
	std::vector<GameObject*>::iterator End();
	void Clear();
private:
	std::vector<GameObject*> objects;
};

extern PhysicsManager* physicsMgr;