#include "Bomb.h"

#include "Transform.h"
#include "Collider.h"
#include "Drawable.h"
#include "ExplodeOnContact.h"

Bomb::Bomb(float xPos, float yPos, float zPos) {
	transform = new Transform();
	drawable = new Drawable();
	collider = new Collider();
	explodeOnContact = new ExplodeOnContact(30);

	transform->position = XMFLOAT3(xPos, yPos, zPos);
	transform->scale = XMFLOAT3(3, 3, 3);
	drawable->getEffectVariables("betterPhong", "Render");
	drawable->createBuffer("Sphere");
	drawable->addTexture("Test2", "diffuseMap");

	components.push_back(transform);
	components.push_back(drawable);
	components.push_back(explodeOnContact);
	components.push_back(collider);
	GameObject::InitComponents();
}

Bomb::~Bomb() {
	delete transform;
	delete drawable;
	delete collider;
	delete explodeOnContact;
}

void Bomb::Draw() {
	drawable->setEffectVariables();
	drawable->setEffectTextures();
	drawable->draw();
}