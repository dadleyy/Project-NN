#include "Spacecraft.h"
#include "Drawable.h"
#include "PlayerControls.h"
#include "PhysicsComponent.h"
#include "..\ResourceManager.h"

extern ResourceManager* drawAtts;

Spacecraft::Spacecraft(ID3D11Device* device, ID3D11DeviceContext* immediateContext, float xPos, float yPos, float zPos)
{
    drawable = new Drawable(device, immediateContext);
    drawable->setPosition(XMFLOAT3(xPos, yPos, zPos));
    drawable->getEffectVariables("betterPhong", "Render");
    drawable->createBuffer("cool");
	drawable->addTexture("Test2", "diffuseMap");
	physics = new PhysicsComponent(drawAtts->camera.GetLook(), drawAtts->camera.GetRight(), drawAtts->camera.GetUp(), 0, 10, 15, XMFLOAT3(0, 0,0), XMFLOAT3(0,0,0), XMFLOAT3(0,0,0), 0, 0);
	playerControls = new PlayerControls();
    components.push_back(drawable);
	components.push_back(physics);
    components.push_back(playerControls);

	physics->Init( this );
	physics->setLinVDamp( .98 );
	physics->setLinADamp( .9 );

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
}
