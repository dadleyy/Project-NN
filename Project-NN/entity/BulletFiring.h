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
	void HandleCollision(GameObject* other);
	void SetActive();
	XMFLOAT3 forward;

private:
	GameObject* go;
	Transform* transform;
	float speed;
	float time;
};
