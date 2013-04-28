#include "PlayerControls.h"

#include <iostream>
using namespace std;

#include "ResourceManager.h"
#include "GameObject.h"
#include "Drawable.h"
#include "PhysicsComponent.h"
#include "input.h"

#define CAMERA_VELOCITY 3.0


bool PlayerControls::Init(GameObject* go) {
	physics = go->GetComponent<PhysicsComponent>();
	fired = false;
	return physics != nullptr;
	fireDelay = 0.0;
}

void PlayerControls::Update(float dt) {
	//fired = false;

	if(fireDelay > 0)
	{
		fireDelay -= dt;
	}
	else if( input->getLMouseButton() && !input->getRMouseButton()) {
		//float rotAngle = -(1 * dt);
		//resourceMgr->camera.RotateY(rotAngle);
		fired = true;
	}/* else if(!input->getLMouseButton() && input->getRMouseButton()) {
		//float rotAngle = (1 * dt);
		//resourceMgr->camera.RotateY(rotAngle);
	}*/

	relMouseX = screenWidth/2.0 - input->getMouseX();
	relMouseY = screenHeight/2.0 - input->getMouseY();

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
		physics->setAcceleration( XMFLOAT3(physics->acceleration.x - .5, physics->acceleration.y, physics->acceleration.z) );
		break;
	case 'W':
		//drawAtts->camera.Walk( CAMERA_VELOCITY * dt );
		physics->setAcceleration( XMFLOAT3(physics->acceleration.x + .5, physics->acceleration.y, physics->acceleration.z) );
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
