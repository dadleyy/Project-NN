#include "AttachLight.h"
#include "PhysicsComponent.h"
class GameObject;

AttachLight::AttachLight(LightStruct* l, PhysicsComponent* p)
{
	light = l;
	physics = p;
}
	
bool AttachLight::Init(GameObject* go)
{
	return true;
}

void AttachLight::Update(float dt)
{
	light->position.x = physics->position.x;
	light->position.y = physics->position.y;
	light->position.z = physics->position.z;

	light->direction.x = physics->forwardAxis.x;
	light->direction.y = physics->forwardAxis.y;
	light->direction.z = physics->forwardAxis.z;
}