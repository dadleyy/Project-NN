#include "DivideOnContact.h"

#include "framework/quaternionMath.h"
#include "PlayerControls.h"
#include "GameObject.h"
#include "Transform.h"
#include "SceneManager.h"


DivideOnContact::DivideOnContact(int divisionsRemaining) {
	this->divisionsRemaining = divisionsRemaining;
}

bool DivideOnContact::Init(GameObject* go) {
	this->go = go;
	return true;
}

void DivideOnContact::HandleCollision(GameObject* other) {
	//We want to make sure that it's the ship that's colliding.
	if(other->GetComponent<PlayerControls>() == nullptr)
		return;

	if(divisionsRemaining > 0) {
		auto obj1 = go->Clone();
		auto obj2 = go->Clone();
		auto obj3 = go->Clone();

		obj1->GetComponent<DivideOnContact>()->divisionsRemaining = divisionsRemaining - 1;
		obj2->GetComponent<DivideOnContact>()->divisionsRemaining = divisionsRemaining - 1;
		obj3->GetComponent<DivideOnContact>()->divisionsRemaining = divisionsRemaining - 1;

		//obj1->transform->position.x += 5;
		obj1->transform->scale = scale(obj1->transform->scale, 0.7f);
		//obj2->transform->position.x -= 5;
		obj2->transform->scale = scale(obj2->transform->scale, 0.7f);
		//obj3->transform->position.y -= 5;
		obj3->transform->scale = scale(obj3->transform->scale, 0.7f);

		sceneMgr->Insert(obj1);
		sceneMgr->Insert(obj2);
		sceneMgr->Insert(obj3);
	}

	sceneMgr->Remove(go);
}