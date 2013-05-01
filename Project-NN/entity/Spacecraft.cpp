#include "Spacecraft.h"

#include "Transform.h"
#include "Drawable.h"
#include "Collider.h"
#include "PlayerControls.h"
#include "PhysicsComponent.h"
#include "PlayerCameraComponent.h"
#include "ResourceManager.h"
#include "BulletManager.h"


Spacecraft::Spacecraft(float xPos, float yPos, float zPos)
{
	transform = new Transform();
    drawable = new Drawable();
	bManager = new BulletManager();
	collider = new Collider();
	transform->position = XMFLOAT3(xPos, yPos, zPos); 
    drawable->getEffectVariables("betterPhong", "Render");
    drawable->createBuffer("cool");
	drawable->addTexture("Test2", "diffuseMap");
	physics = new PhysicsComponent(resourceMgr->camera.GetLook(), resourceMgr->camera.GetRight(), resourceMgr->camera.GetUp(), 0, 10, 15, XMFLOAT3(0, 0,0), XMFLOAT3(0,0,0), XMFLOAT3(0,0,0), 0, 0);
	playerControls = new PlayerControls();
	playerCamera = new PlayerCameraComponent(&resourceMgr->camera);

    components.push_back(transform);
    components.push_back(drawable);
	components.push_back(bManager);
    components.push_back(collider);
	components.push_back(physics);
	components.push_back(playerCamera);
    components.push_back(playerControls);

	physics->setLinVDamp( .90 );
	physics->setLinADamp( .90 );

	GameObject::InitComponents();
}

void Spacecraft::Draw()
{
	drawable->setEffectVariables();
	drawable->setEffectTextures();
    drawable->draw();
}

Spacecraft::~Spacecraft(void)
{
	delete transform;
    delete drawable;
	delete collider;
	delete playerCamera;
    delete playerControls;
	delete physics;
}
