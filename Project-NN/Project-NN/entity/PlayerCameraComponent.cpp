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
	lagDistance = 8;
}


PlayerCameraComponent::~PlayerCameraComponent(void)
{
}

void PlayerCameraComponent::Init(GameObject* go)
{
	object = go;
	lerpFor = new float3LERP();
	lerpPos = new float3LERP();
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

	//camera->SetLook(objectPhysics->forwardAxis);
	// camera->SetUp(objectPhysics->upAxis);
	// camera->SetRight(objectPhysics->sideAxis);
	lerpFor->goal = objectPhysics->forwardAxis;
	lerpFor->start = camera->GetLook();
	float change = acos(dotProduct(lerpFor->goal, lerpFor->start))/(PI/2);

	camera->SetUp(objectPhysics->upAxis);
	camera->SetRight(objectPhysics->sideAxis);
	camera->SetLook(objectPhysics->forwardAxis);

	//camera->SetLook( normalize(scale(lerpFor->lerp(  dt , change), -1)) );

	float ld = lagDistance + ( vecmag( objectPhysics->velocity ) * 0.333f );

	if( ld < lagDistance )
		ld = lagDistance;

	//lerpPos->start = camera->GetPosition();

	XMFLOAT3 pos = add(objectPhysics->position, scale(objectPhysics->forwardAxis, -ld));
	


	//XMFLOAT3 reflectAxis = scale(normalize(objectPhysics->forwardAxis), -1);
	//XMFLOAT3 cameraRelPosition = add( objectPhysics->position, scale(camera->GetPosition(), -1));
	//XMFLOAT3 reflectedVector = add(cameraRelPosition, scale(reflectAxis, -2*dotProduct(reflectAxis, cameraRelPosition)));
	//lerpPos->start = add( objectPhysics->position, reflectedVector);

	//lerpPos->goal = add(objectTransform->position, scale(pos, -1));

	//pos = lerpPos->lerp( dt, 10);
	
	XMFLOAT3 offset( objectControls->relMouseX, objectControls->relMouseY, 0.0 );
	offset = offset;

	XMFLOAT3 sideChange = scale(objectPhysics->sideAxis, 3*2*offset.x/screenWidth);
	XMFLOAT3 upChange = scale(objectPhysics->upAxis,   3*2*offset.y/screenHeight);

	pos.x += sideChange.x + upChange.x;
	pos.y += sideChange.y + upChange.y;
	pos.z += sideChange.z + upChange.z;

	//camera->LookAt(pos, objectPhysics->position, objectPhysics->upAxis);

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