#pragma once
#include "Component.h"

class Camera;
class Transform;
class PhysicsComponent;

class PlayerCameraComponent :
	public Component
{
public:
	PlayerCameraComponent(Camera* cam);
	~PlayerCameraComponent(void);
	void Init( GameObject* go );
	void Update(float dt);
	void smoothFollow(float dt);

	float lagDistance;


	Transform* objectTransform;
	PhysicsComponent* objectPhysics;

	GameObject* object;
	Camera* camera;
	
};

