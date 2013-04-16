#include "PlayerCameraComponent.h"
#include "..\framework\quaternionMath.h"
#include "..\framework\Camera.h"
#include "GameObject.h"
#include "PhysicsComponent.h"
#include "PlayerControls.h"
#include "Transform.h"

XMFLOAT3 normalize(XMFLOAT3 v);
float vecmag( XMFLOAT3 v );

PlayerCameraComponent::PlayerCameraComponent(Camera* cam)
{
	camera = cam;
	lagDistance = 8;
}


PlayerCameraComponent::~PlayerCameraComponent(void)
{
}

void PlayerCameraComponent::Init(GameObject* go)
{
	object = go;
	objectTransform = object->GetComponent<Transform>();
	objectPhysics = object->GetComponent<PhysicsComponent>();
	objectControls = object->GetComponent<PlayerControls>();
}

void PlayerCameraComponent::Update(float dt) 
{
	smoothFollow(dt);
	//camera->LookAt( camera->GetPosition(), objectPhysics->position, objectPhysics->upAxis );
}

void PlayerCameraComponent::smoothFollow(float dt)
{
	float angleUp = acos( abs(objectPhysics->upAxis.x*camera->GetUp().x + objectPhysics->upAxis.y*camera->GetUp().y + objectPhysics->upAxis.z*camera->GetUp().z) -.001 ); 
	float angleForw = acos( abs(objectPhysics->forwardAxis.x*camera->GetLook().x + objectPhysics->forwardAxis.y*camera->GetLook().y + objectPhysics->forwardAxis.z*camera->GetLook().z) -.001 );
	float totalAngle = abs(angleForw) + abs(angleUp);

	camera->SetLook(objectPhysics->forwardAxis);
	// camera->SetUp(objectPhysics->upAxis);
	// camera->SetRight(objectPhysics->sideAxis);
	
	float ld = lagDistance + ( vecmag( objectPhysics->velocity ) * 0.333f );

	if( ld < lagDistance )
		ld = lagDistance;

	XMFLOAT3 pos = XMFLOAT3( 
							camera->GetLook().x * ( ld + (objectControls->relMouseX * 0.0025f) ), 
							camera->GetLook().y * ( ld + (objectControls->relMouseY * 0.0025f) ), 
							camera->GetLook().z * ld );
	camera->SetPosition( 
		XMFLOAT3 (	objectTransform->position.x - pos.x, 
					objectTransform->position.y - pos.y, 
					objectTransform->position.z - pos.z ) );

	//float anglePercent = totalAngle/PI;
	//camera->SetLook( normalize(add(scale(camera->GetLook(),anglePercent*dt) , scale(objectPhysics->forwardAxis,(1-anglePercent)*dt))) );
	//camera->SetUp( normalize(add(scale(camera->GetUp(),anglePercent*dt) , scale(objectPhysics->upAxis,(1-anglePercent)*dt))) );
	//camera->SetRight( normalize(add(scale(camera->GetRight(),anglePercent*dt) , scale(objectPhysics->sideAxis,(1-anglePercent)*dt))) );

}

float vecmag(  XMFLOAT3 v )
{
	float k = v.x*v.x + v.y*v.y + v.z*v.z;
	k = sqrt( k );
	return k;
}

XMFLOAT3 normalize(XMFLOAT3 v)
{
	float k = v.x*v.x + v.y*v.y + v.z*v.z;

	if( (k <= .99 || k >= 1.01) && k != 0)
	{
		k = sqrt(k);
		v.x /= k;
		v.y /= k;
		v.z /= k;
	}

	return v;
}