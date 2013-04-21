#include "Bomb.h"

#include "Transform.h"
#include "Drawable.h"

Bomb::Bomb(float xPos, float yPos, float zPos) {
	transform = new Transform();
	drawable = new Drawable();

	transform->position = XMFLOAT3(xPos, yPos, zPos);

	components.push_back(transform);
	components.push_back(drawable);
}

Bomb::~Bomb() {
	drawable->destroy();
}