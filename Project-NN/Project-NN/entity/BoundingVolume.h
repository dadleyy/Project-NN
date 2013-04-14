#pragma once

#include "entity/Component.h"

class GameObject;
class Transform;

class BoundingVolume : public Component {
public:
	BoundingVolume();
	void Init(GameObject* go);
	void Update(float dt);

	virtual bool IsColliding(GameObject* other);

private:
	Transform* transform;
};
