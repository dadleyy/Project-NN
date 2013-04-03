#include "Spacecraft.h"
#include "Drawable.h"
#include "Wobble.h"

Spacecraft::Spacecraft(ID3D11Device* device, ID3D11DeviceContext* immediateContext, float xPos, float yPos, float zPos)
{
    wobble = new Wobble();
    sphere = new Drawable(device, immediateContext);
    sphere->setPosition(XMFLOAT3(xPos, yPos, zPos));
    sphere->getEffectVariables("sphereEffect", "Render");
    sphere->createBuffer("CoolObject");
    components.push_back(sphere);
    components.push_back(wobble);
	GameObject::InitComponents();
}

void Spacecraft::Draw()
{
    sphere->draw();
}

Spacecraft::~Spacecraft(void)
{
    sphere->destroy();
    delete sphere;
    delete wobble;
}
