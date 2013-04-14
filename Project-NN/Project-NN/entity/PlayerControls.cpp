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
        resourceMgr->camera.Strafe( -CAMERA_VELOCITY * dt );
        break;
    case 'D':
        resourceMgr->camera.Strafe( CAMERA_VELOCITY * dt );
        break;
    case 'S':
        resourceMgr->camera.Walk( -CAMERA_VELOCITY * dt );
        break;
    case 'W':
        resourceMgr->camera.Walk( CAMERA_VELOCITY * dt );
        break;
	case 'X':
		physics->setAcceleration( XMFLOAT3(physics->acceleration.x + .2, 0, 0) );

    default:
        break;
    }
}
