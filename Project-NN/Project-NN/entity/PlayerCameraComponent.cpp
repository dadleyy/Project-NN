#include "PlayerCameraComponent.h"
#include "..\framework\quaternionMath.h"
#include "..\framework\Camera.h"
#include "GameObject.h"
#include "PhysicsComponent.h"
#include "Transform.h"
#include "..\framework\quaternionMath.h"

PlayerCameraComponent::PlayerCameraComponent(Camera* cam)
{
	camera = cam;
	lagDistance = 10;
}


PlayerCameraComponent::~PlayerCameraComponent(void)
{
}

void PlayerCameraComponent::Init(GameObject* go)
{
	object = go;
	objectTransform = object->GetComponent<Transform>();
	objectPhysics = object->GetComponent<PhysicsComponent>();
}

void PlayerCameraComponent::Update(float dt) 
{
	XMFLOAT3 pos = XMFLOAT3( objectPhysics->forwardAxis.x * lagDistance, objectPhysics->forwardAxis.y * lagDistance, objectPhysics->forwardAxis.z * lagDistance );
	camera->SetPosition( XMFLOAT3(objectTransform->position.x - pos.x, objectTransform->position.y - pos.y, objectTransform->position.z - pos.z ) );
	
	camera->LookAt( camera->GetPosition(), objectPhysics->position, objectPhysics->upAxis );
}

void PlayerCameraComponent::smoothFollow(float dt)
{
	float angleUp = acos( objectPhysics->upAxis.x*camera->GetUp().x + objectPhysics->upAxis.y*camera->GetUp().y + objectPhysics->upAxis.z*camera->GetUp().z ); 
	XMFLOAT3 crossUp = XMFLOAT3( objectPhysics->upAxis.y*camera->GetUp().z - objectPhysics->upAxis.z*camera->GetUp().y,
								 objectPhysics->upAxis.z*camera->GetUp().x - objectPhysics->upAxis.x*camera->GetUp().z,
								 objectPhysics->upAxis.x*camera->GetUp().y - objectPhysics->upAxis.y*camera->GetUp().x);

	Quaternion qU( angleUp, crossUp );
}