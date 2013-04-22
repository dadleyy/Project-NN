#include "PlayerCameraComponent.h"
#include "..\framework\quaternionMath.h"
#include "..\framework\Camera.h"
#include "GameObject.h"
#include "PhysicsComponent.h"
#include "PlayerControls.h"
#include "Transform.h"
#include "..\framework\LERP.h"

XMFLOAT3 normalize(XMFLOAT3 v);
float vecmag( XMFLOAT3 v );

extern int screenWidth;
extern int screenHeight;

PlayerCameraComponent::PlayerCameraComponent(Camera* cam)
{
	camera = cam;
	baseFOV = cam->GetFovY();
	lagDistance = 15;
}


PlayerCameraComponent::~PlayerCameraComponent(void)
{
}

bool PlayerCameraComponent::Init(GameObject* go)
{
	object = go;
	objectTransform = object->GetComponent<Transform>();
	objectPhysics = object->GetComponent<PhysicsComponent>();
	objectControls = object->GetComponent<PlayerControls>();
	return objectPhysics != nullptr
		&& objectTransform != nullptr
		&& objectControls != nullptr;
}

void PlayerCameraComponent::Update(float dt) 
{
	smoothFollow(dt);
}

void PlayerCameraComponent::smoothFollow(float dt)
{
	camera->SetUp(objectPhysics->upAxis);
	camera->SetRight(objectPhysics->sideAxis);
	camera->SetLook(objectPhysics->forwardAxis);

	float ld = lagDistance + ( objectPhysics->speed * 0.333f );
	float fovD = objectPhysics->speed * 2*(PI/180);
	if(fovD > 45*(PI/180))
		fovD = 45*(PI/180);
	
	if( ld < lagDistance )
		ld = lagDistance;

	camera->SetLens(baseFOV+fovD, camera->GetAspect(), camera->GetNearZ(), camera->GetFarZ());

	XMFLOAT3 pos = add(objectPhysics->position, scale(objectPhysics->forwardAxis, -ld));
	
	XMFLOAT3 offset( objectControls->relMouseX, objectControls->relMouseY, 0.0 );
	offset = offset;

	XMFLOAT3 sideChange = scale(objectPhysics->sideAxis, -sign(offset.x)*pow(2*offset.x/screenWidth, 2));
	XMFLOAT3 upChange = scale(objectPhysics->upAxis,     sign(offset.y)*pow(2*offset.y/screenHeight, 2));

	pos.x += sideChange.x + upChange.x;
	pos.y += sideChange.y + upChange.y;
	pos.z += sideChange.z + upChange.z;

	camera->SetPosition( pos );
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