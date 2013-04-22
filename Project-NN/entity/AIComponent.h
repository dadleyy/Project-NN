
#pragma once

#include <Windows.h>
#include <xnamath.h>
#include "entity/Component.h"

class GameObject;
class PhysicsComponent;
class Transform;

enum AI_STATE {
	AI_FOLLOWING,
	AI_STANDING,
	AI_WANDER
};

class AIComponent : public Component {

public:
	AIComponent( );
	bool Init(GameObject* go);
	void Update( float dt );

	void SetTarget(GameObject* t);
	void SetState(int state);


private:

	void Follow( float dt );
	void Stand( float dt );
	void Wander( float dt );
	
	XMFLOAT3 distV;
	float    distL;

	AI_STATE state;

	PhysicsComponent* objPhysics;
	Transform* objTransform;

	PhysicsComponent* tarPhysics;
	Transform* tarTransform;
};

