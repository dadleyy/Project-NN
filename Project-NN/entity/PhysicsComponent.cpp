#include "PhysicsComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "PlayerControls.h"

void normalize(XMFLOAT3* v);
XMFLOAT3 norm( XMFLOAT3 v );
float magnitudeSq( XMFLOAT3 v );

void damp(float* s, float damp, float minDamp, float dt);
void damp(XMFLOAT3* v, float damp, float minDamp, float dt);
float magnitude(XMFLOAT3 v );

PhysicsComponent::PhysicsComponent( XMFLOAT3 fAxis, XMFLOAT3 sAxis, XMFLOAT3 uAxis,
                                    float m, float sp, float m_sp, XMFLOAT3 pos, XMFLOAT3 vel,
                                    XMFLOAT3 acc, float angularVel, float angularAcc) : MIN_DAMP(.005) {
	mass = m;
	speed = sp;
	MAX_SPEED = m_sp;
	MAX_ACCEL = 10000;
	position = pos;
	velocity = vel;
	acceleration = acc;
	angularVelocity = angularVel;
	angularAcceleration = angularAcc;
	forwardAxis = fAxis;
	sideAxis = sAxis;
	upAxis = uAxis;
}


PhysicsComponent::~PhysicsComponent(void) {
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
void PhysicsComponent::setAxis( XMFLOAT3 f, XMFLOAT3 u, XMFLOAT3 s ) {
	forwardAxis = f;
	upAxis = u;
	sideAxis = s;
}

bool PhysicsComponent::Init(GameObject* go) {
	object = go;
	transform = object->GetComponent<Transform>();
	return transform != nullptr;
}

void PhysicsComponent::Update(float dt) {
	//artificially dampen the acceleration
	damp(&acceleration, accelerationDamp, MIN_DAMP, dt);
	//artificially dampen the speed
	damp(&speed, velocityDamp, MIN_DAMP, dt);

	if(magnitudeSq(acceleration) > MAX_SPEED*MAX_SPEED)
	{
		acceleration = scale(norm(acceleration),MAX_SPEED);
	}
	
	if( magnitude( acceleration ) > MAX_ACCEL ){
		acceleration = scale( norm( acceleration ), MAX_ACCEL );
	}
		

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

	// recalculate orientation from axis
	XMMATRIX rotation;

	rotation._11 = sideAxis.x;
	rotation._12 = sideAxis.y;
	rotation._13 = sideAxis.z;
	rotation._14 = 0.0f;

	rotation._21 = upAxis.x;
	rotation._22 = upAxis.y;
	rotation._23 = upAxis.z;
	rotation._24 = 0.0f;

	rotation._31 = forwardAxis.x;
	rotation._32 = forwardAxis.y;
	rotation._33 = forwardAxis.z;
	rotation._34 = 0.0f;

	rotation._41 = 0.0f;
	rotation._42 = 0.0f;
	rotation._43 = 0.0f;
	rotation._44 = 1.0f;

	//XMMATRIX rotation = XMMatrixLookAtLH( mpos, tpos, up );
	XMVECTOR quat = XMQuaternionRotationMatrix( rotation );
	XMStoreFloat4( &transform->rotation, quat );

	//update the position
	position = XMFLOAT3( position.x + (velocity.x*forwardAxis.x + velocity.y*sideAxis.x + velocity.z*upAxis.x)*dt,
	                     position.y + (velocity.x*forwardAxis.y + velocity.y*sideAxis.y + velocity.z*upAxis.y)*dt,
	                     position.z + (velocity.x*forwardAxis.z + velocity.y*sideAxis.z + velocity.z*upAxis.z)*dt);

	transform->position = position;
}

void damp(XMFLOAT3* v, float damp, float minDamp, float dt) 
{
	float dampFrame = 1-damp*dt;
	v->x = v->x*dampFrame; if(abs(v->x) < minDamp) v->x = 0;
	v->y = v->y*dampFrame; if(abs(v->y) < minDamp) v->y = 0;
	v->z = v->z*dampFrame; if(abs(v->z) < minDamp) v->z = 0;
}

void damp(float* s, float damp, float minDamp, float dt) 
{
	float dampFrame = 1-damp*dt;
	(*s) = (*s)*dampFrame; if((*s) < minDamp) (*s) = 0;
}

float magnitude( XMFLOAT3 v ) {
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

float magnitudeSq( XMFLOAT3 v ) {
	return v.x*v.x + v.y*v.y + v.z*v.z;
}

void normalize(XMFLOAT3* v) {
	float k = v->x*v->x + v->y*v->y + v->z*v->z;

	if( (k <= .99 || k >= 1.01) && k != 0) {
		k = sqrt(k);
		v->x /= k;
		v->y /= k;
		v->z /= k;
	}
}

XMFLOAT3 norm( XMFLOAT3 v ){
	XMFLOAT3 result( v.x, v.y, v.z );

	float k = v.x*v.x + v.y*v.y + v.z*v.z;

	if( (k <= .99 || k >= 1.01) && k != 0) {
		k = sqrt(k);
		result.x /= k;
		result.y /= k;
		result.z /= k;
	}

	return result;
}
