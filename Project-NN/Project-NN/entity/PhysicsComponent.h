#pragma once
#include "Component.h"
#include <Windows.h>
#include <xnamath.h>

class GameObject;
class Transform;

class PhysicsComponent :
	public Component
{
public:
	PhysicsComponent(void);
	PhysicsComponent( XMFLOAT3 fAxis, XMFLOAT3 sAxis, XMFLOAT3 uAxis, 
				float mass, float speed, float m_speed, XMFLOAT3 position, XMFLOAT3 velocity, 
				XMFLOAT3 acceleration, float angularVelocity, float angularAcceleration);
	~PhysicsComponent(void);

	void Init( GameObject* go );
	void Update(float dt);
	void Impulse( XMFLOAT3 vector, float magnitude );

	//Properties
	//**************************************
	void setMass( float m );
	void setSpeed( float m );
	void setMaxSpeed( float m );
	void setLinVDamp( float m );
	void setLinADamp( float m );

	void setPosition( XMFLOAT3 v );
	void setVelocity( XMFLOAT3 v );
	void setAcceleration( XMFLOAT3 v );
	void setQuaternion( XMFLOAT4 v );
	//**************************************

	GameObject* object;
	Transform* transform;

	const float MIN_DAMP;

	float mass;
	float speed;
	float MAX_SPEED;
	float friction;
	float velocityDamp;
	float accelerationDamp;
	float angVelocityDamp;
	float angAccelerationDamp;

	XMFLOAT3 position;
	XMFLOAT4 quaternion;
	float angularVelocity;
	float angularAcceleration;
	XMFLOAT3 velocity;
	XMFLOAT3 acceleration;
	//moment of inertia tensor

	//axis for velocity to use to update position
	XMFLOAT3 forwardAxis;
	XMFLOAT3 sideAxis;
	XMFLOAT3 upAxis;
};

