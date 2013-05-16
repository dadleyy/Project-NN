#include "Enemy.h"

#include "Transform.h"
#include "Drawable.h"
#include "PhysicsComponent.h"
#include "AIComponent.h"
#include "..\ResourceManager.h"


Enemy::Enemy(GameObject* initialTarget, XMFLOAT3 initialPosition )
{
	
	ai = new AIComponent( );	
	transform = new Transform( );
	drawable = new Drawable( );

	physics = new PhysicsComponent( 
		resourceMgr->camera.GetLook(), 
		resourceMgr->camera.GetRight(), 
		XMFLOAT3(0.0f, 1.0f, 0.0f), 
		0, 10, 15, 
		initialPosition,
		XMFLOAT3(0,0,0), 
		XMFLOAT3(0,0,0), 
		0, 0 
	);
	

	transform->position = initialPosition; 
	drawable->getEffectVariables("betterPhong", "Render");
	drawable->setShader("betterPhong", "Render");
	drawable->createBuffer("cool");
	drawable->addTexture("shipTexture", "diffuseMap");


	physics->setLinVDamp( .98 );
	physics->setLinADamp( .9975 );
	physics->minSpeed = 3;

	ai->SetTarget( initialTarget );

	components.push_back(transform);
	components.push_back(drawable);
	components.push_back(physics);
	components.push_back(ai);

	GameObject::InitComponents();
}

void Enemy::Draw()
{
	drawable->setEffectVariables();
	drawable->setEffectTextures();
	drawable->draw();
}