#include "PhysicsComponent.h"
#include "PlayerControls.h"
#include "GameObject.h"
#include "Transform.h"
#include "..\framework\quaternionMath.h"
#include "Health.h"

void damp(float* s, float damp, float minDamp, float dt);
void damp(XMFLOAT3* v, float damp, float minDamp, float dt);
int frameNumber;


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
	frameNumber = 0;
	angVelocityDamp = 0;
	friction = 0;
	quaternion = Quaternion(1,0,0,0);
	minSpeed = 0;
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
	position = transform->position;
	//artificially dampen the acceleration
	damp(&acceleration, accelerationDamp, MIN_DAMP, dt);
	//artificially dampen the speed
	damp(&speed, velocityDamp, MIN_DAMP, dt);

	if(magnitudeSq(acceleration) > MAX_SPEED*MAX_SPEED)
	{
		acceleration = scale(normalize(acceleration),MAX_SPEED);
	}		

	

	velocity = XMFLOAT3( velocity.x + acceleration.x*dt,
	                     velocity.y + acceleration.y*dt,
	                     velocity.z + acceleration.z*dt );

	if(velocity.x < 0)
		velocity.x  = 0;
	//normalize the velocity, multiply by speed, and add the acceleration from the last frame
	speed = magnitude( velocity );

	//clamp speed between 0 and max speed
	if(speed > MAX_SPEED) 
	{
		speed = MAX_SPEED;
		velocity = scale(normalize(velocity), MAX_SPEED);
	}
	if(speed < minSpeed)
	{
		speed = minSpeed;
		velocity = scale(normalize(velocity), minSpeed);
	}

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

	Quaternion q(1, 0, 0, 0);
	if(angularVelocity > 0)
	{
		if(angularVelocity > 40)
			angularVelocity = 40;
		damp(&angularVelocity, angVelocityDamp, MIN_DAMP, dt);
		q = Quaternion(angularVelocity*dt, rotAxis);
		quaternion = mult(quaternion, q);
	}

	//XMMATRIX rotation = XMMatrixLookAtLH( mpos, tpos, up );
	XMVECTOR quat = XMQuaternionRotationMatrix( rotation );
	XMVECTOR angs = XMLoadFloat4(&XMFLOAT4(quaternion.x, quaternion.y, quaternion.z, quaternion.w)); 
	quat = XMQuaternionMultiply(angs,quat);
	XMStoreFloat4( &transform->rotation, quat );

	

	worldvelocity = XMFLOAT3(velocity.x*forwardAxis.x + velocity.y*sideAxis.x + velocity.z*upAxis.x,
							 velocity.x*forwardAxis.y + velocity.y*sideAxis.y + velocity.z*upAxis.y,
							 velocity.x*forwardAxis.z + velocity.y*sideAxis.z + velocity.z*upAxis.z);

	//update the position
	position = XMFLOAT3( position.x + (worldvelocity.x)*dt,
	                     position.y + (worldvelocity.y)*dt,
	                     position.z + (worldvelocity.z)*dt);

	transform->position = position;
	frameNumber++;
}

void PhysicsComponent::HandleCollision(GameObject* go)
{
	PhysicsComponent* goPC = go->GetComponent<PhysicsComponent>();

	if(goPC == 0) return;
	if(mass == 0 || goPC->mass == 0) return;
	float totalMass = mass + goPC->mass;

	//Move these apart to when they were just touching, then move them apart just a little more
	float distApart = magnitude(XMFLOAT3( position.x - goPC->position.x, position.y - goPC->position.y, position.z - goPC->position.z ));
	distApart = transform->scale.x + goPC->transform->scale.x - distApart;
	float delta = distApart/magnitude( add(worldvelocity, scale(goPC->worldvelocity, -1)) ) + .01;
	position = add( scale(worldvelocity, -delta), position );
	goPC->position = add( scale(goPC->worldvelocity, -delta), goPC->position );

	float momentum1 = mass*speed;
	float momentum2 = goPC->mass*goPC->speed;

	XMFLOAT3 collisionNormal = normalize(XMFLOAT3(position.x - goPC->position.x, position.y - goPC->position.y, position.z - goPC->position.z));
	XMFLOAT3 inverseCollisionNormal = scale(collisionNormal, -1);
	float proj1 = abs(dotProduct(worldvelocity, inverseCollisionNormal));
	float proj2 = abs(dotProduct(goPC->worldvelocity, collisionNormal));

	//the magnitude of the collision
	float impact = proj1*mass + proj2*goPC->mass;

	//reduce health based on impact
	Health* h1 = object->GetComponent<Health>();
	Health* h2 = go->GetComponent<Health>();
	if(impact < 50000000000)
	{
		if(h1)
		{
			if(object->GetComponent<PlayerControls>())
				h1->Damage(impact/1000);
		}
		if(h2)
		{
			if(go->GetComponent<PlayerControls>())
				h2->Damage(impact/1000);
		}
	}

	float impact2 = (impact*mass)/(totalMass*totalMass);
	float impact1 = (impact*goPC->mass)/(totalMass*totalMass);

	worldvelocity = XMFLOAT3( worldvelocity.z - inverseCollisionNormal.x*impact1, worldvelocity.y - inverseCollisionNormal.y*impact1, worldvelocity.x - inverseCollisionNormal.z*impact1);
	
	velocity = XMFLOAT3(worldvelocity.x*forwardAxis.x + worldvelocity.y*forwardAxis.y + worldvelocity.z*forwardAxis.z,
						worldvelocity.x*sideAxis.x    + worldvelocity.y*sideAxis.y    + worldvelocity.z*sideAxis.z,
						worldvelocity.x*upAxis.x      + worldvelocity.y*upAxis.y      + worldvelocity.z*upAxis.z);

	goPC->worldvelocity = XMFLOAT3( goPC->worldvelocity.z - collisionNormal.x*impact2, goPC->worldvelocity.y - collisionNormal.y*impact2, goPC->worldvelocity.x - collisionNormal.z*impact2);

	goPC->velocity = XMFLOAT3(goPC->worldvelocity.x*goPC->forwardAxis.x + goPC->worldvelocity.y*goPC->forwardAxis.y + goPC->worldvelocity.z*goPC->forwardAxis.z,
						      goPC->worldvelocity.x*goPC->sideAxis.x    + goPC->worldvelocity.y*goPC->sideAxis.y    + goPC->worldvelocity.z*goPC->sideAxis.z,
							  goPC->worldvelocity.x*goPC->upAxis.x      + goPC->worldvelocity.y*goPC->upAxis.y      + goPC->worldvelocity.z*goPC->upAxis.z);

	//handle friction
	if(friction*goPC->friction != 0)
	{
		float resistance = impact*(friction + goPC->friction)/1000000;
		float angVel1 = magnitude(XMFLOAT3( worldvelocity.z - inverseCollisionNormal.x*proj1, worldvelocity.y - inverseCollisionNormal.y*proj1, worldvelocity.x - inverseCollisionNormal.z*proj1));
		float angVel2 = magnitude(XMFLOAT3( goPC->worldvelocity.z - collisionNormal.x*proj2, goPC->worldvelocity.y - collisionNormal.y*proj2, goPC->worldvelocity.x - collisionNormal.z*proj2));
		XMFLOAT3 rotAxis1 = normalize(cross(worldvelocity, inverseCollisionNormal));
		XMFLOAT3 rotAxis2 = normalize(cross(goPC->worldvelocity, collisionNormal));
		
		angularVelocity += angVel1*resistance;
		rotAxis = normalize(add(rotAxis,rotAxis1));

		goPC->angularVelocity += angVel2*resistance;
		goPC->rotAxis = normalize(add(goPC->rotAxis,rotAxis2));
	}
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
