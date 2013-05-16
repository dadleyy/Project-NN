#pragma once
#include "Light.h"

#include "Component.h"
class PhysicsComponent;
class GameObject;

class AttachLight : public Component {
public:
	AttachLight(LightStruct* light, PhysicsComponent* physics);
	bool Init(GameObject* go);
	void Update(float dt);
private:
	 LightStruct* light;
	 PhysicsComponent* physics;
};