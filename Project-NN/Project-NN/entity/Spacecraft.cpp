#include "Spacecraft.h"

#include "Transform.h"
#include "Drawable.h"
#include "PlayerControls.h"
#include "PhysicsComponent.h"
#include "PlayerCameraComponent.h"
#include "..\ResourceManager.h"


Spacecraft::Spacecraft(ID3D11Device* device, ID3D11DeviceContext* immediateContext, float xPos, float yPos, float zPos)
{
	transform = new Transform();
    drawable = new Drawable(device, immediateContext);
	transform->position = XMFLOAT3(xPos, yPos, zPos); 
    drawable->getEffectVariables("betterPhong", "Render");
    drawable->createBuffer("cool");
	drawable->addTexture("Test2", "diffuseMap");
	physics = new PhysicsComponent(resourceMgr->camera.GetLook(), resourceMgr->camera.GetRight(), resourceMgr->camera.GetUp(), 0, 10, 15, XMFLOAT3(0, 0,0), XMFLOAT3(0,0,0), XMFLOAT3(0,0,0), 0, 0);
	playerControls = new PlayerControls();
	playerCamera = new PlayerCameraComponent(&resourceMgr->camera);

    components.push_back(transform);
    components.push_back(drawable);
	components.push_back(physics);
	components.push_back(playerCamera);
    components.push_back(playerControls);

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
	delete transform;
}
