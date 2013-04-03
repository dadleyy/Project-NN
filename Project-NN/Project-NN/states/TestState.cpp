#include "TestState.h"

#include "StateManager.h"
#include "entity/Drawable.h"
#include "entity/Asteroid.h"
#include "entity/Spacecraft.h"

#include <iostream>
#include <random>

#define CAMERA_VELOCITY 3.0

using namespace std;

TestState TestState::instance;
extern ResourceManager* drawAtts;

void TestState::Init(StateManager* manager)
{
	GameState::Init(manager);

    mouseDown = false;
    currentmouseposition[0] = currentmouseposition[1] = 0;
    lastmouseposition[0] = lastmouseposition[1] = 0;

    spacer = 0;


	uniform_real_distribution<float> distribution(-10, 10);
	
	for(int i = 0; i < 2; i++) {
		asteroids.push_back(new Asteroid(manager->GetDevice(), manager->GetContext(),
			distribution(drawAtts->randomEngine), distribution(drawAtts->randomEngine), distribution(drawAtts->randomEngine)));
	}


    if( drawAtts->addMesh("objs/spacecraft.obj","CoolObject") ){
        cout << "okay loading" << endl;
        spacer = new Spacecraft(manager->GetDevice(), manager->GetContext(), 0, 0, 0 );
    } else {
        cout << "not okay loading" << endl;
    }

	cout << "Initting" << endl;
    
	drawAtts->camera.SetLens(0.25f*MathHelper::Pi, 800.0f/600.0f, 0.01f, 100.0f);
	drawAtts->camera.SetPosition(XMFLOAT3(0.5f, 0.5f, -1.0f));
}

void TestState::Cleanup()
{
	for(auto it = asteroids.begin(); it != asteroids.end(); ++it) {
		delete *it;
	}
    delete spacer;
}

void TestState::handleKey( int keycode, float dt )
{
    // cout << keycode << endl;
    switch(keycode)
    {
    case 81:
        drawAtts->camera.Strafe( -CAMERA_VELOCITY * dt );
        break;
    case 69:
        drawAtts->camera.Strafe( CAMERA_VELOCITY * dt );
        break;
    case 83:
        drawAtts->camera.Walk( -CAMERA_VELOCITY * dt );
        break;
    case 87:
        drawAtts->camera.Walk( CAMERA_VELOCITY * dt );
        break;
    default:
        break;
    }
}

void TestState::Update(float dt)
{

    if( mouseDown ) {
        float rotAngle = (1 * dt);
        drawAtts->camera.RotateY(rotAngle);
    }

    for( int i = 0; i < 256; i++ ){
        if( manager->keystates[i] )
            handleKey( i, dt ); 
    }

    int dx = currentmouseposition[0] - ( screenWidth * 0.5 );
    drawAtts->camera.RotateY( (dx / ( screenWidth * 0.5 )) * dt );
    
    int dy = currentmouseposition[1] - ( screenHeight * 0.5 );
    drawAtts->camera.Pitch( (dy / ( screenHeight * 0.5 )) * dt);
    


	XMFLOAT3 pos    = drawAtts->camera.GetPosition( );
	XMFLOAT3 target = XMFLOAT3(0, 0, 0);
	XMFLOAT3 up     = XMFLOAT3(0.0f, 1.0f, 0.0f);

	//drawAtts->camera.LookAt(pos, target, up);

    drawAtts->camera.UpdateViewMatrix();

	for(auto it = asteroids.begin(); it != asteroids.end(); ++it) {
		(*it)->Update(dt);
	}


    lastmouseposition[0] = currentmouseposition[0];
    lastmouseposition[1] = currentmouseposition[1];
}

void TestState::Draw()
{
	for(auto it = asteroids.begin(); it != asteroids.end(); ++it) {
		(*it)->Draw();
	}
    
    if( spacer != 0 )
        spacer->Draw( );
}

void TestState::OnMouseMove(int x, int y)
{
    currentmouseposition[0] = x;
    currentmouseposition[1] = y;
}

void TestState::OnMouseDown(int x, int y)
{
	cout << "mouse down" << endl;
    mouseDown = true;

	cout << drawAtts->camera.GetPosition().z << endl;
}

void TestState::OnMouseUp(int x, int y)
{
    cout << "mouse up" << endl;
    mouseDown = false;
}