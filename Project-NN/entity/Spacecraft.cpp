#include "Spacecraft.h"

#include "Transform.h"
#include "Drawable.h"
#include "Collider.h"
#include "PlayerControls.h"
#include "PhysicsComponent.h"
#include "PlayerCameraComponent.h"
#include "ResourceManager.h"
#include "BulletManager.h"
#include "AttachLight.h"
#include "PlayerGameplay.h"
#include "Health.h"

Spacecraft::Spacecraft(float xPos, float yPos, float zPos)
{
	damage = 10;
	transform = new Transform();
    drawable = new Drawable();
	bManager = new BulletManager();
	collider = new Collider();
	transform->position = XMFLOAT3(xPos, yPos, zPos); 
    drawable->getEffectVariables("betterPhong", "Render");
	drawable->setShader("betterPhong", "Render");
    drawable->createBuffer("cool");
	drawable->addTexture("shipTexture", "diffuseMap");
	
	physics = new PhysicsComponent(resourceMgr->camera.GetLook(), resourceMgr->camera.GetRight(), resourceMgr->camera.GetUp(), 0, 10, 15, XMFLOAT3(0, 0,0), XMFLOAT3(1,0,0), XMFLOAT3(0,0,0), 0, 0);
	physics->mass = 10000;
	physics->angVelocityDamp = 500;
	physics->friction = -.14;
	physics->minSpeed = 5;
	playerControls = new PlayerControls();
	playerCamera = new PlayerCameraComponent(&resourceMgr->camera);

    components.push_back(transform);
    components.push_back(drawable);
    components.push_back(collider);
	components.push_back(physics);
	components.push_back(playerCamera);
    components.push_back(playerControls);
	components.push_back(bManager);
	components.push_back(new Health(200));
	components.push_back(new PlayerGameplay());
	components.push_back(new AttachLight(resourceMgr->lights[2], physics));

	physics->setLinVDamp( .95 );
	physics->setLinADamp( .95 );

	GameObject::InitComponents();
}

void Spacecraft::Draw()
{
	drawable->setEffectVariables();
	drawable->setEffectTextures();
    drawable->draw();
}
