#pragma once
#include "Component.h"

class Camera;
class Transform;
class PhysicsComponent;
class PlayerControls;

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
	PlayerControls* objectControls;

	GameObject* object;
	Camera* camera;
	
};

