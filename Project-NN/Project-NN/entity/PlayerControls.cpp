#include "PlayerControls.h"

#include <iostream>
using namespace std;

#include "ResourceManager.h"
#include "GameObject.h"
#include "Drawable.h"
#include "PhysicsComponent.h"
#include "input.h"

#define CAMERA_VELOCITY 3.0


void PlayerControls::Init(GameObject* go) 
{
	physics = go->GetComponent<PhysicsComponent>();
}

void PlayerControls::Update(float dt) {
	if( input->getLMouseButton() && !input->getRMouseButton()) {
        float rotAngle = -(1 * dt);
        resourceMgr->camera.RotateY(rotAngle);
    }
	else if(!input->getLMouseButton() && input->getRMouseButton())
	{
		float rotAngle = (1 * dt);
        resourceMgr->camera.RotateY(rotAngle);
	}

	relMouseX = screenWidth/2.0 - input->getMouseX();
	relMouseY = screenHeight/2.0 - input->getMouseY();

    for( int i = 0; i < 256; i++ ){
        if(// manager->keystates[i]
			input->getKeyDown(i))
		{
            handleKey( i, dt ); 
		}
    }

}

void PlayerControls::handleKey( int keycode, float dt )
{
     cout << keycode << endl;
    switch(keycode)
    {
    case 'A':
        //drawAtts->camera.Strafe( -CAMERA_VELOCITY * dt );
		physics->setAcceleration( XMFLOAT3(physics->acceleration.x, physics->acceleration.y - 2, physics->acceleration.z));
		break;
    case 'D':
        //drawAtts->camera.Strafe( CAMERA_VELOCITY * dt );
		physics->setAcceleration( XMFLOAT3(physics->acceleration.x, physics->acceleration.y + 2, physics->acceleration.z));
        break;
    case 'S':
        //drawAtts->camera.Walk( -CAMERA_VELOCITY * dt );
		physics->setAcceleration( XMFLOAT3(physics->acceleration.x - 2, physics->acceleration.y, physics->acceleration.z) );
        break;
    case 'W':
        //drawAtts->camera.Walk( CAMERA_VELOCITY * dt );
		physics->setAcceleration( XMFLOAT3(physics->acceleration.x + 2, physics->acceleration.y, physics->acceleration.z) );     
        break;
/*	case 'Q':
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
		break;*/
    default:
        break;
    }
}
