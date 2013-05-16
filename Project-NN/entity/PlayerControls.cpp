#include "PlayerControls.h"

#include <iostream>
using namespace std;

#include "ResourceManager.h"
#include "GameObject.h"
#include "Drawable.h"
#include "PhysicsComponent.h"
#include "BulletManager.h"
#include "input.h"

#define CAMERA_VELOCITY 3.0


bool PlayerControls::Init(GameObject* go) {
	shooting = false;

	physics = go->GetComponent<PhysicsComponent>();
	bManager = go->GetComponent<BulletManager>();
	fired = false;
	return physics != nullptr;
	fireDelay = 0.0;
}

void PlayerControls::Update(float dt) {
	//fired = false;

	if(fireDelay > 0) {
		fireDelay -= dt;
	} else if( input->getLMouseButton() && !input->getRMouseButton()) {
		bManager->Fire();
		fireDelay = .4;
	}

	if( input->getLMouseButton( ) ) {
		if( !shooting )
			resourceMgr->setCursor("shooting");
		shooting = true;
	} else {
		if( shooting )
			resourceMgr->setCursor("default");
		shooting = false;
	}

	relMouseX = screenWidth/2.0 - input->getMouseX();
	relMouseY = screenHeight/2.0 - input->getMouseY();

	relMouseX = sign(relMouseX)*(max(0,abs(relMouseX) - 40));
	relMouseY = sign(relMouseY)*(max(0,abs(relMouseY) - 25));

	//update the rotation
	float rotAngle = -180 * ( relMouseY / ( screenHeight / 2.0 ) );
	Quaternion q( rotAngle*dt, physics->sideAxis );
	rotAngle = -180 * ( relMouseX / ( screenWidth / 2.0 ) );
	q = mult( q, Quaternion( rotAngle*dt, physics->upAxis ) );

	physics->forwardAxis = transformVector(q, physics->forwardAxis);
	physics->upAxis = transformVector(q, physics->upAxis);
	physics->sideAxis = transformVector(q, physics->sideAxis);

	for( int i = 0; i < 256; i++ ) {
		if(// manager->keystates[i]
		    input->getKeyDown(i)) {
			handleKey( i, dt );
		}
	}

}

void PlayerControls::handleKey( int keycode, float dt ) {
	switch(keycode) {
	case 'A':
		//drawAtts->camera.Strafe( -CAMERA_VELOCITY * dt );
		physics->setAcceleration( XMFLOAT3(physics->acceleration.x, physics->acceleration.y - .5, physics->acceleration.z));
		break;
	case 'D':
		//drawAtts->camera.Strafe( CAMERA_VELOCITY * dt );
		physics->setAcceleration( XMFLOAT3(physics->acceleration.x, physics->acceleration.y + .5, physics->acceleration.z));
		break;
	case 'S':
		//drawAtts->camera.Walk( -CAMERA_VELOCITY * dt );
		if(physics->velocity.x > .5)
			physics->setAcceleration( XMFLOAT3(physics->acceleration.x - .5, physics->acceleration.y, physics->acceleration.z) );
		break;
	case 'W':
		//drawAtts->camera.Walk( CAMERA_VELOCITY * dt );
		physics->setAcceleration( XMFLOAT3(physics->acceleration.x + .5, physics->acceleration.y, physics->acceleration.z) );
		break;
	case 'B':
		//drawAtts->camera.Walk( CAMERA_VELOCITY * dt );
		physics->setAcceleration( XMFLOAT3(0,0,0) );
		physics->setVelocity(XMFLOAT3(0,0,0));
		physics->setSpeed(0);
		break;
		/*
	case 'Q':
		drawAtts->camera.Walk( CAMERA_VELOCITY * dt );
		break;
	case 'E':
		drawAtts->camera.Walk( -CAMERA_VELOCITY * dt );
		break;
	case 'Z':
		drawAtts->camera.Strafe( -CAMERA_VELOCITY * dt );
		break;
	case 'C':
		drawAtts->camera.Strafe( CAMERA_VELOCITY * dt );
		break;
		*/
	default:
		break;
	}
}
