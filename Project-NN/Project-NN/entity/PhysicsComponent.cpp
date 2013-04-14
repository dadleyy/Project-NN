#include "PhysicsComponent.h"
#include "GameObject.h"
#include "Transform.h"

void normalize(XMFLOAT3* v);
void damp(float* s, float damp, float minDamp);
void damp(XMFLOAT3* v, float damp, float minDamp);
float magnitude(XMFLOAT3 v );

PhysicsComponent::PhysicsComponent( XMFLOAT3 fAxis, XMFLOAT3 sAxis, XMFLOAT3 uAxis, 
				float m, float sp, float m_sp, XMFLOAT3 pos, XMFLOAT3 vel, 
				XMFLOAT3 acc, float angularVel, float angularAcc) : MIN_DAMP(.005)
{
	mass = m;
	speed = sp;
	MAX_SPEED = m_sp;
	position = pos;
	velocity = vel;
	acceleration = acc;
	angularVelocity = angularVel;
	angularAcceleration = angularAcc;

	forwardAxis = fAxis;
	sideAxis = sAxis;
	upAxis = uAxis;
}


PhysicsComponent::~PhysicsComponent(void)
{
}


void PhysicsComponent::setMass        ( float m )    { mass = m; }
void PhysicsComponent::setSpeed       ( float m )    { speed = m; }
void PhysicsComponent::setMaxSpeed    ( float m )    { MAX_SPEED = m; }
void PhysicsComponent::setLinVDamp    ( float m )    { velocityDamp = m; }
void PhysicsComponent::setLinADamp    ( float m )    { accelerationDamp = m; }
void PhysicsComponent::setPosition    ( XMFLOAT3 v ) { position = v; }
void PhysicsComponent::setVelocity    ( XMFLOAT3 v ) { velocity = v; }
void PhysicsComponent::setAcceleration( XMFLOAT3 v ) { acceleration = v; }
void PhysicsComponent::setQuaternion  ( XMFLOAT4 v ) { quaternion = v; }

void PhysicsComponent::Init(GameObject* go)
{
	object = go;
	transform = object->GetComponent<Transform>();
}

void PhysicsComponent::Update(float dt) 
{
	speed = magnitude( velocity );

	if(abs(speed) > MAX_SPEED)
		speed < 0 ? speed = -MAX_SPEED : speed = MAX_SPEED;

	damp(&acceleration, accelerationDamp, MIN_DAMP);
	damp(&speed, velocityDamp, MIN_DAMP);

	normalize( &velocity );
	velocity = XMFLOAT3( velocity.x*speed + acceleration.x*dt,
						 velocity.y*speed + acceleration.y*dt, 
						 velocity.z*speed + acceleration.z*dt );

	position = XMFLOAT3( position.x + (velocity.x*forwardAxis.x + velocity.y*sideAxis.x + velocity.z*upAxis.x)*dt, 
						 position.y + (velocity.x*forwardAxis.y + velocity.y*sideAxis.y + velocity.z*upAxis.y)*dt,
						 position.z + (velocity.x*forwardAxis.z + velocity.y*sideAxis.z + velocity.z*upAxis.z)*dt);


	transform->position = position;
}

void damp(XMFLOAT3* v, float damp, float minDamp)
{
	v->x = v->x*damp; if(abs(v->x) < minDamp) v->x = 0;
	v->y = v->y*damp; if(abs(v->y) < minDamp) v->y = 0;
	v->z = v->z*damp; if(abs(v->z) < minDamp) v->z = 0;
}

void damp(float* s, float damp, float minDamp)
{
	(*s) = (*s)*damp; if((*s) < minDamp) (*s) = 0;
}

float magnitude( XMFLOAT3 v )
{
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

void normalize(XMFLOAT3* v)
{
	float k = v->x*v->x + v->y*v->y + v->z*v->z;

	if( (k <= .99 || k >= 1.01) && k != 0)
	{
		k = sqrt(k);
		v->x /= k;
		v->y /= k;
		v->z /= k;
	}
}