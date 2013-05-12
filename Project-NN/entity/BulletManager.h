#pragma once

#include <vector>
//#include "GameObject.h"
#include "entity/Component.h"

class GameObject;
class Transform;
class PhysicsComponent;
class Bullet;

class BulletManager : public Component {
public:
	bool Init(GameObject* go);
	void Update(float dt);
	void Fire();

	std::vector<Bullet*> bullets;
private:
	GameObject* go;
	//Transform* transform;
};
