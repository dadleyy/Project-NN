#include "Enemy.h"

#include "Transform.h"
#include "Drawable.h"
#include "PhysicsComponent.h"
#include "AIComponent.h"
#include "..\ResourceManager.h"


Enemy::Enemy(GameObject* initialTarget, XMFLOAT3 initialPosition )
{
	
	transform = new Transform( );
	drawable = new Drawable( );

	ai = new AIComponent( );	
	physics = new PhysicsComponent( 
		resourceMgr->camera.GetLook(), 
		resourceMgr->camera.GetRight(), 
		XMFLOAT3(0.0f, 1.0f, 0.0f), 
		0, 10, 15, 
		XMFLOAT3(0, 0,0), 
		XMFLOAT3(0,0,0), 
		XMFLOAT3(0,0,0), 
		0, 0 
	);
	

	transform->position = initialPosition; 
	drawable->getEffectVariables("betterPhong", "Render");
	drawable->createBuffer("cool");
	drawable->addTexture("quickie", "diffuseMap");

	physics->setLinVDamp( .98 );
	physics->setLinADamp( .9975 );

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

Enemy::~Enemy(void)
{
	delete drawable;
	delete transform;
	delete ai;
	delete physics;
}
