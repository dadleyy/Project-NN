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

AIComponent::AIComponent( ) : uid("ai_")
{
	state = AI_FOLLOWING;
	strength = 10.0f;
	AI::flockers.insert( this );

	std::ostringstream con;
	con << AI::flockers.size(  );
	uid.append( con.str( ) );
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
	XMVECTOR force = XMVectorZero( );

	switch( state ){
	case AI_FOLLOWING:
		force = XMVectorAdd( Follow(dt), force );
		break;
	case AI_STANDING:
		force = XMVectorAdd( Stand(dt), force );
		break;
	case AI_WANDER:
		force = XMVectorAdd( Wander(dt), force );
		break;
	default:
		force = XMVectorAdd( Stand(dt), force );
		break;
	}

	// save a temp reference to the original target
	GameObject* temp = target;
	// add a flocking force 
	force = XMVectorAdd( Flock(dt), force );
	// set the target back to the original
	target = temp;

	// at this point, force is a vector that has been manipulated with behaviors
	XMVECTOR forward = XMVector3Normalize( force );
	XMVECTOR up = XMLoadFloat3( &source->GetComponent<PhysicsComponent>( )->upAxis );
	XMVECTOR side = XMVector3Normalize( XMVector3Cross( up, forward ) );

	// save the new calculated axis's
	XMStoreFloat3( &source->GetComponent<PhysicsComponent>()->forwardAxis, forward );
	XMStoreFloat3( &source->GetComponent<PhysicsComponent>()->sideAxis, side );
	XMStoreFloat3( &source->GetComponent<PhysicsComponent>()->upAxis, up );

	// add forces to velocity
	XMStoreFloat3( &source->GetComponent<PhysicsComponent>( )->velocity, force );

}

XMVECTOR AIComponent::Flock( float dt )
{	
	float closest_d = 0;
	AIComponent* closest_ai;

	for( auto i = AI::flockers.begin( ); i != AI::flockers.end( ); ++i ){
		if( (*i)->uid == uid )
			continue;
		
		XMVECTOR tpos = XMLoadFloat3( &(*i)->source->GetComponent<Transform>( )->position );
		XMVECTOR mpos = XMLoadFloat3( &source->GetComponent<Transform>( )->position );
		XMVECTOR diff = XMVectorSubtract( tpos, mpos );
		float diff_length = XMVectorGetX( XMVector3Length( diff ) );
		if( closest_d == 0 || diff_length < closest_d ){
			closest_d = diff_length;
			closest_ai = (*i);
		}

	}
	target = closest_ai->source;
	
	return Avoid( dt );
}

XMVECTOR AIComponent::Avoid( float dt )
{
	XMVECTOR tpos = XMLoadFloat3( &target->GetComponent<Transform>()->position );
	XMVECTOR mpos = XMLoadFloat3( &source->GetComponent<Transform>()->position );
	XMVECTOR diff = XMVectorScale( XMVectorSubtract( tpos, mpos ), -1.0f );
	XMVECTOR a_force = XMVector3Normalize( diff );
	float length = XMVectorGetX( XMVector3Length( diff ) );
	a_force = XMVectorScale( a_force, 1.0f );

	XMVECTOR out = XMVectorZero( );
	return out;
}

XMVECTOR AIComponent::Follow( float dt )
{
	XMVECTOR tpos = XMLoadFloat3( &target->GetComponent<Transform>()->position );
	XMVECTOR mpos = XMLoadFloat3( &source->GetComponent<Transform>()->position );
	XMVECTOR diff = XMVectorSubtract( tpos, mpos );
	XMVECTOR f_force = XMVector3Normalize( diff );
	// calculate how large this force vector should be
	float length = XMVectorGetX( XMVector3Length( diff ) );
	f_force = XMVectorScale( f_force, pow( (length * 0.5f), 2.0f ) );
	// send that out
	return f_force;
}

XMVECTOR AIComponent::Stand( float dt )
{

	return XMVectorZero();
}

XMVECTOR AIComponent::Wander( float dt )
{

	return XMVectorZero();
}