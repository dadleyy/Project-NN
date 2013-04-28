#pragma once

#include <vector>
#include <set>

class GameObject;


class PhysicsManager {
public:
	void AddObject(GameObject* go);
	void RemoveObject(GameObject* go);
	void CheckForCollisions();
	//Called after a frame to add/remove GameObjects.
	void Process();
	std::vector<GameObject*>::iterator Begin();
	std::vector<GameObject*>::iterator End();
private:
	std::vector<GameObject*> objects;
	std::set<GameObject*> inserted;
	std::set<GameObject*> deleted;
};

extern PhysicsManager* physicsMgr;