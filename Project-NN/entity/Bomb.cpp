#include "Bomb.h"

#include "Transform.h"
#include "Collider.h"
#include "Drawable.h"
#include "ExplodeOnContact.h"
#include "Wobble.h"

Bomb::Bomb(float xPos, float yPos, float zPos) {
	transform = new Transform();
	drawable = new Drawable();
	collider = new Collider();
	explodeOnContact = new ExplodeOnContact(30);
	glowColorMode = 1;
	damage = 0;
	transform->position = XMFLOAT3(xPos, yPos, zPos);
	transform->scale = XMFLOAT3(3, 3, 3);
	drawable->getEffectVariables("betterPhongBump", "Render");

	drawable->setShader("betterPhongBump", "Render");
	drawable->addTexture("bomb", "diffuseMap");
	drawable->addTexture("bombBump", "bumpMap");

	drawable->getEffectVariables("glowDraw", "RenderGlowy");
	drawable->setShader("glowDraw", "RenderGlowy");
	drawable->addEffectVariables("glowColorMode", "colorMode", &glowColorMode);
	drawable->addTexture("bombGlow", "glowTex");
	drawable->addTexture("Depth", "depth");

	drawable->setShader("betterPhongBump", "Render");
	
	drawable->createBuffer("Sphere");
	
	glow = true;

	components.push_back(transform);
	components.push_back(drawable);
	components.push_back(explodeOnContact);
	components.push_back(collider);
	//components.push_back(new Wobble());
	GameObject::InitComponents();
}

void Bomb::Draw() {
	drawable->setEffectVariables();
	drawable->setEffectTextures();
	drawable->draw();
}