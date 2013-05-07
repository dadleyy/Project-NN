#include "AIComponent.h"

#include "GameObject.h"
#include "Transform.h"
#include "PhysicsComponent.h"
#include "ResourceManager.h"

#include <unordered_set>
#include <sstream>
#include <random>

namespace AI {
	std::unordered_set<AIComponent*> flockers;
}

AIComponent::AIComponent( ) : auid("ai_")
{
	state = AI_FOLLOWING;
	strength = 10.0f;
	AI::flockers.insert( this );
	ostringstream os;
	os << AI::flockers.size();
	auid.append( os.str( ) );
}

AIComponent::~AIComponent ( ) {
	AI::flockers.erase( this );
}

void AIComponent::SetTarget(GameObject* t) {
	target = t;
}

void AIComponent::SetState(int s){ state = state; }

bool AIComponent::Init(GameObject* go)
{
	source = go;
	return go != nullptr;
}

void AIComponent::Update( float dt )
{
	
	desired = source->GetComponent<PhysicsComponent>( )->forwardAxis;

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
	
	Flock( dt );

	XMVECTOR finalf = XMLoadFloat3( &desired );
	// calculate new rotation axis
	XMVECTOR up = XMLoadFloat3( &source->GetComponent<PhysicsComponent>()->upAxis );
	XMVECTOR side = XMVector3Normalize( XMVector3Cross( up, finalf ) );

	// save the new axis into the obj
	XMStoreFloat3( &source->GetComponent<PhysicsComponent>()->forwardAxis, finalf );
	XMStoreFloat3( &source->GetComponent<PhysicsComponent>()->upAxis, up );
	XMStoreFloat3( &source->GetComponent<PhysicsComponent>()->sideAxis, side );

	source->GetComponent<PhysicsComponent>( )->acceleration.x += (strength * dt);
}

void AIComponent::Wander( float dt )
{
	
}
void AIComponent::Flock( float dt )
{	
	// save the current target
	GameObject* temp = target;
	// set the initial closest dist and closest ai
	float cdist = 0;
	XMFLOAT3 dist;
	AIComponent* closest;
	// start looping other ai components
	for( auto oai = AI::flockers.begin( ); oai != AI::flockers.end( ); ++oai ) {
		// skip this ai component
		if( (*oai)->auid == auid )
			continue;
		
		XMVECTOR tpos = XMLoadFloat3( &(*oai)->source->GetComponent<Transform>( )->position );
		XMVECTOR mpos = XMLoadFloat3( &source->GetComponent<Transform>( )->position );
		// calculate the distance
		XMVECTOR diff = XMVectorSubtract( mpos, tpos );
		XMStoreFloat3( &dist, XMVector3Length( diff ) );
		// set this to the closest if it is
		if( cdist == 0 || dist.x < cdist ){
			closest = (*oai);
			cdist = dist.x;
		}
	}
	SetTarget( closest->source );
	Avoid( dt );

	// set the target back to the original
	SetTarget( temp );
}
void AIComponent::Avoid( float dt )
{
	// store the postions as vectors
	XMVECTOR tpos = XMLoadFloat3( &target->GetComponent<Transform>()->position );
	XMVECTOR mpos = XMLoadFloat3( &source->GetComponent<Transform>()->position );

	// calculate the difference, save it
	XMVECTOR diff = XMVectorScale( XMVectorSubtract( tpos, mpos ), -1.0f );
	XMVECTOR dest_forward = XMVector3Normalize( diff );
	
	XMFLOAT3 mag;
	XMStoreFloat3( &mag, XMVector3Length( diff ) );
	float factor = 1.0f / (mag.x * 0.10f);
	if( factor > 1.0f )
		factor = 1.0f;

	strength += factor * 10000.0f;
	// adjust based on dist
	XMVECTOR dd = XMLoadFloat3( &desired );
	XMStoreFloat3( &desired, XMVectorLerp( dd, dest_forward, factor ) );

}

void AIComponent::Follow( float dt )
{
	// store the postions as vectors
	XMVECTOR tpos = XMLoadFloat3( &target->GetComponent<Transform>()->position );
	XMVECTOR mpos = XMLoadFloat3( &source->GetComponent<Transform>()->position );

	// calculate the difference, save it
	XMVECTOR diff = XMVectorSubtract( tpos, mpos );
	XMVECTOR dest_forward = XMVector3Normalize( diff );
	
	// save the magnitude
	XMFLOAT3 mag;
	XMStoreFloat3( &mag, XMVector3Length( diff ) );
	
	float factor = mag.x * 0.10f;
	if( factor > 1.0f )
		factor = 1.0f;

	// adjust based on dist
	XMVECTOR dd = XMLoadFloat3( &desired );
	XMStoreFloat3( &desired, XMVectorLerp( dd, dest_forward, factor ) );

}

void AIComponent::Stand( float dt )
{

}
