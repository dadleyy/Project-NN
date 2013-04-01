#pragma once

#include "entity/Component.h"
#include <Windows.h>
#include <xnamath.h>

class GameObject;
class Drawable;

/**
 * Makes gameobjects wobble back and forth.
 *
 * Requires the Drawable component.
 */
class Wobble : public Component {
public:
	void Init(GameObject* go);
	void Update(float dt);

private:
	Drawable* drawable;
	XMFLOAT3 basePosition;
	float totalTime;
};