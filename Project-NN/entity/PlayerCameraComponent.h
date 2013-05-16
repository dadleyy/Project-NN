#pragma once
#include "Component.h"

class Camera;
class Transform;
class PhysicsComponent;
class PlayerControls;
class float3LERP;

class PlayerCameraComponent :
	public Component
{
public:
	PlayerCameraComponent(Camera* cam);
	~PlayerCameraComponent();
	bool Init( GameObject* go );
	void Update(float dt);
	void smoothFollow(float dt);

	float lagDistance;
	float baseFOV;		//the fov of the camera with no velocity

	Transform* objectTransform;
	PhysicsComponent* objectPhysics;
	PlayerControls* objectControls;

	GameObject* object;
	Camera* camera;
	
};

