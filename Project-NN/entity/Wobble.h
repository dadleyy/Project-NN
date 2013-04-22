#pragma once

#include "entity/Component.h"
#include <Windows.h>
#include <xnamath.h>

class GameObject;
class Transform;

/**
 * Makes gameobjects wobble back and forth.
 *
 * Requires the Drawable component.
 */
class Wobble : public Component {
public:
	bool Init(GameObject* go);
	void Update(float dt);

private:
	Transform* transform;
	XMFLOAT3 basePosition;
	float totalTime;
};
