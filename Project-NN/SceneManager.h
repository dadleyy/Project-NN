#pragma once

#include <unordered_set>
#include <queue>

class GameObject;

class SceneManager {
public:
	//Inserts the given GameObject at the end of the frame.
	void Insert(GameObject* go);
	//Removes and deletes the given GameObject at the end of the frame.
	void Remove(GameObject* go);

	//Call at the end of the frame to add/remove GameObjects from scene.
	void Process();

	std::unordered_set<GameObject*>::iterator Begin();
	std::unordered_set<GameObject*>::iterator End();
	void Clear();

private:
	std::unordered_set<GameObject*> sceneObjects;
	std::queue<GameObject*> inserted;
	std::queue<GameObject*> deleted;
};

extern SceneManager* sceneMgr;