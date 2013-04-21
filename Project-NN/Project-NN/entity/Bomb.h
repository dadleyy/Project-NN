#pragma once

#include "GameObject.h"

class Bomb : public GameObject {
public:
	Bomb(float xPos, float yPos, float zPos);
	virtual ~Bomb();
	void Draw();

private:
	Transform* transform;
	Drawable* drawable;
};