#include "BulletManager.h"

#include <Windows.h>
#include <xnamath.h>

#include "PhysicsComponent.h"
#include "GameObject.h"
#include "Bullet.h"
#include "Transform.h"
#include "PhysicsManager.h"


BulletManager::~BulletManager() {
	physicsMgr->RemoveObject(go);
}

bool BulletManager::Init(GameObject* go) {
	this->go = go;
	
	transform = go->GetComponent<Transform>();
	physicsMgr->AddObject(go);
	return transform != nullptr;
}

void BulletManager::Update(float dt) {
}

void BulletManager::Fire(){
	for(auto it = bullets.begin(); it != bullets.end(); ++it) {
		if((*it)->active)
			continue;
		else
		{
			(*it)->setForward(go->GetComponent<PhysicsComponent>()->forwardAxis);
			(*it)->transform->position = transform->position;
			(*it)->active = true;
			return;
		}
	}
	for(auto it = bullets.begin(); it != bullets.end(); ++it){
			(*it)->setForward(go->GetComponent<PhysicsComponent>()->forwardAxis);
			(*it)->transform->position = transform->position;
			return;
	}

}