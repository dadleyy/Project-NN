#include "PhysicsComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "PlayerControls.h"

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
	quaternion = Quaternion();
	forwardAxis = fAxis;
	sideAxis = sAxis;
	upAxis = uAxis;

	//RigidBody[] = not OBB
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
void PhysicsComponent::setQuaternion  ( XMFLOAT4 v ) { quaternion.x = v.x; quaternion.y = v.y; quaternion.z = v.z; quaternion.w = v.w; }
void PhysicsComponent::setAxis( XMFLOAT3 f, XMFLOAT3 u, XMFLOAT3 s )
{
	forwardAxis = f;
	upAxis = u;
	sideAxis = s;
}

void PhysicsComponent::Init(GameObject* go)
{
	object = go;
	transform = object->GetComponent<Transform>();
	control = object->GetComponent<PlayerControls>();
}

void PhysicsComponent::Update(float dt) 
{
	//artificially dampen the acceleration
	damp(&acceleration, accelerationDamp, MIN_DAMP);
	//artificially dampen the speed
	damp(&speed, velocityDamp, MIN_DAMP);

	if(acceleration.x > 0)
		int kjsdl = 1;

	//normalize the velocity, multiply by speed, and add the acceleration from the last frame 
	normalize( &velocity );
	velocity = XMFLOAT3( velocity.x*speed + acceleration.x*dt,
						 velocity.y*speed + acceleration.y*dt, 
						 velocity.z*speed + acceleration.z*dt );

	//get the new speed from the velocity
	speed = magnitude( velocity );

	//clamp speed between 0 and max speed
	if(speed > MAX_SPEED) speed = MAX_SPEED;
	if( speed < 0 ) speed = 0;

	
	//update the rotation
	float rotAngle = -control->relMouseY;
	Quaternion q(rotAngle/3600.0, sideAxis);

	rotAngle = -control->relMouseX;
	q = mult(q, Quaternion(rotAngle/3600.0, upAxis));

	quaternion = mult(q, quaternion);
	transform->rotation = XMFLOAT4(quaternion.x, quaternion.y, quaternion.z, quaternion.w);

	forwardAxis = transformVector(q, forwardAxis);
	upAxis = transformVector(q, upAxis);
	sideAxis = transformVector(q, sideAxis);

	//update the position
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