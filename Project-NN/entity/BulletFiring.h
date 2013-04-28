#pragma once

#include "GameObject.h"
#include "entity/Component.h"

class GameObject;
class Transform;

class BulletFiring : public Component {
public:
	~BulletFiring();
	bool Init(GameObject* go, XMFLOAT3* forward, int speed);
	void Update(float dt);

private:
	GameObject* go;
	Transform* transform;
	int speed;
	XMFLOAT3* forward;
};
