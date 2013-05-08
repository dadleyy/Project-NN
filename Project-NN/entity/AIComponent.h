
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

private:

	void Follow( float dt );
	void Stand( float dt );
	void Wander( float dt );
	void Flock( float dt );
	void Avoid( float dt );
	
	AI_STATE state;
	XMFLOAT3 desired;
	float strength;

};

