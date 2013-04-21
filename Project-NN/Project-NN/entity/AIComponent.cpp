#include "AIComponent.h"

#include "GameObject.h"
#include "Transform.h"
#include "PhysicsComponent.h"
#include "ResourceManager.h"

#include <iostream>
#include <random>
using namespace std;

XMFLOAT3 norm( XMFLOAT3 v );
float vecmag(  XMFLOAT3 v );

AIComponent::AIComponent( )
{
	state = AI_FOLLOWING;
}

void AIComponent::SetTarget(GameObject* t) { 
	tarPhysics = t->GetComponent<PhysicsComponent>( ); 
	tarTransform = t->GetComponent<Transform>( );
}

void AIComponent::SetState(int s){ state = state; }

bool AIComponent::Init(GameObject* go)
{
	objPhysics = go->GetComponent<PhysicsComponent>( );
	objTransform = go->GetComponent<Transform>( );
	return objTransform != nullptr && objPhysics != nullptr;
}

void AIComponent::Update( float dt )
{
	
	switch( state ){
	case AI_FOLLOWING:
		Follow( dt );
		break;
	case AI_STANDING:
		Stand( dt );
		break;
	case AI_WANDER:
		Wander( dt );
		break;
	default:
		Wander( dt );
		break;
	}

}

void AIComponent::Wander( float dt )
{
	
}

void AIComponent::Follow( float dt )
{
	// store the postions as vectors
	XMVECTOR tpos = XMLoadFloat3( &tarTransform->position );
	XMVECTOR mpos = XMLoadFloat3( &objTransform->position );

	// calculate the differemce, save it
	XMVECTOR diff = XMVectorSubtract( tpos, mpos );
	XMStoreFloat3( &distV, diff );
	distL = vecmag( distV );

	// calculate new rotation axis
	XMVECTOR up = XMLoadFloat3( &objPhysics->upAxis );
	XMVECTOR forward = XMVector3Normalize( diff );
	XMVECTOR side = XMVector3Normalize( XMVector3Cross( up, forward ) );

	// save the new axis into the obj
	XMStoreFloat3( &objPhysics->forwardAxis, forward );
	XMStoreFloat3( &objPhysics->upAxis, up );
	XMStoreFloat3( &objPhysics->sideAxis, side );

	// set the velocity and acceleration
	XMStoreFloat3( &objPhysics->velocity, forward );
	XMStoreFloat3( &objPhysics->acceleration, diff );

	objPhysics->acceleration = scale( objPhysics->acceleration, 1000.0f * dt );

	if( true )
		int k = 10;

}

void AIComponent::Stand( float dt )
{

}
