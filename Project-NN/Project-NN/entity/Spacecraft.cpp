#include "Spacecraft.h"

#include "Transform.h"
#include "Drawable.h"
#include "PlayerControls.h"

Spacecraft::Spacecraft(ID3D11Device* device, ID3D11DeviceContext* immediateContext, float xPos, float yPos, float zPos)
{
	transform = new Transform();
    drawable = new Drawable(device, immediateContext);
	transform->position = XMFLOAT3(xPos, yPos, zPos); 
    drawable->getEffectVariables("betterPhong", "Render");
    drawable->createBuffer("Sphere");
	drawable->addTexture("Test", "diffuseMap");
    components.push_back(transform);
    components.push_back(drawable);
    components.push_back(playerControls);
	GameObject::InitComponents();
}

void Spacecraft::Draw()
{
    drawable->draw();
}

Spacecraft::~Spacecraft(void)
{
    drawable->destroy();
    delete drawable;
    delete playerControls;
	delete transform;
}
