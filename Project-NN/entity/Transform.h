#pragma once

#include "entity/Component.h"

#include <Windows.h>
#include <xnamath.h>

class Transform : public Component {
public:
	Transform();
	void Update(float dt);

	XMFLOAT3 position;
	XMFLOAT4 rotation;
	XMFLOAT3 scale;
};