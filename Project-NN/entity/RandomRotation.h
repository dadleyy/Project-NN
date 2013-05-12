#pragma once

#include "entity/Component.h"

class GameObject;
class Transform;

/**
 * Makes gameobjects rotate randomly.
 *
 * Requires the Drawable component.
 */
class RandomRotation : public Component {
public:
	bool Init(GameObject* go);
	void Update(float dt);

private:
	Transform* transform;
};