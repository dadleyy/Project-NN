#pragma once

#include "GameObject.h"
#include "entity/Component.h"

class Bullet;
class GameObject;
class Transform;

class BulletFiring : public Component {
public:
	bool Init(GameObject* go);
	void Update(float dt);

	XMFLOAT3 forward;

private:
	GameObject* go;
	Transform* transform;
	int speed;
};
