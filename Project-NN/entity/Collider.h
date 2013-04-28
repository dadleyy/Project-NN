#pragma once

#include "entity/Component.h"

class GameObject;
class Transform;

class Collider : public Component {
public:
	~Collider();
	bool Init(GameObject* go);
	void Update(float dt);

	virtual bool IsColliding(GameObject* other);

private:
	GameObject* go;
	Transform* transform;
};
