
#pragma once

#include <Windows.h>
#include <xnamath.h>
#include "entity/Component.h"
#include <iostream>

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
	~AIComponent(  );
	bool Init(GameObject* go);
	void Update( float dt );

	void SetTarget(GameObject* t);
	void SetState(int state);

	GameObject *source;
	GameObject *target;

	std::string uid;

private:

	XMVECTOR Follow( float dt );
	XMVECTOR Stand( float dt );
	XMVECTOR Wander( float dt );
	XMVECTOR Flock( float dt );
	XMVECTOR Avoid( float dt );
	
	AI_STATE state;
	float strength;

};

