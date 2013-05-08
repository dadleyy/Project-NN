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

AIComponent::AIComponent( )
{
	state = AI_FOLLOWING;
	strength = 10.0f;
	AI::flockers.insert( this );
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
	
}

void AIComponent::Wander( float dt )
{
	
}
void AIComponent::Flock( float dt )
{	
	
}
void AIComponent::Avoid( float dt )
{
	

}

void AIComponent::Follow( float dt )
{


}

void AIComponent::Stand( float dt )
{

}
