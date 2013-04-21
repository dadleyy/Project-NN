#include "Bomb.h"

#include "Transform.h"
#include "Drawable.h"

Bomb::Bomb(float xPos, float yPos, float zPos) {
	transform = new Transform();
	drawable = new Drawable();

	transform->position = XMFLOAT3(xPos, yPos, zPos);
	drawable->getEffectVariables("betterPhong", "Render");
	drawable->createBuffer("Sphere");
	drawable->addTexture("Test2", "diffuseMap");

	components.push_back(transform);
	components.push_back(drawable);
	GameObject::InitComponents();
}

Bomb::~Bomb() {
	delete transform;
	delete drawable;
}

void Bomb::Draw() {
	drawable->setEffectVariables();
	drawable->setEffectTextures();
	drawable->draw();
}