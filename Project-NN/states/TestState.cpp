#include "TestState.h"

#include <iostream>
#include <random>
#include <unordered_set>

#include "StateManager.h"
#include "entity/Drawable.h"
#include "entity/Drawables/DrawableInstancedModel.h"
#include "entity/Asteroid.h"
#include "entity/Bomb.h"
#include "entity/Enemy.h"
#include "entity/Bullet.h"
#include "entity/Spacecraft.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "input.h"
#include "entity/PlayerControls.h"
#include "entity/Transform.h"
#include "entity/Skybox.h"


using namespace std;

TestState TestState::instance;


void TestState::Init(StateManager* manager) {
	GameState::Init(manager);

	currentmouseposition[0] = currentmouseposition[1] = 0;
	lastmouseposition[0] = lastmouseposition[1] = 0;

	sceneMgr->Insert(new Spacecraft(0.0, 0.0, 0.0));

	asteroidDraw = new DrawableInstancedModel();
	asteroidDraw->getEffectVariables("bumpInstancePhong", "Render");
	asteroidDraw->createBuffer("Asteroid");
	asteroidDraw->addTexture("asteroid", "diffuseMap");
	asteroidDraw->addTexture("asteroidBump", "bumpMap");

	uniform_real_distribution<float> distribution(-100, 100);

	for(int i = 0; i < 1; i++) {
		auto asteroid = new Asteroid(distribution(resourceMgr->randomEngine), distribution(resourceMgr->randomEngine), distribution(resourceMgr->randomEngine), &asteroids);
		sceneMgr->Insert(asteroid);
		asteroids.push_back(asteroid);
	}

	uniform_real_distribution<float> bombDistribution(-30, 30);

	for(int i = 0; i < 20; i++) {
		sceneMgr->Insert(new Bomb(
			bombDistribution(resourceMgr->randomEngine),
			bombDistribution(resourceMgr->randomEngine),
			bombDistribution(resourceMgr->randomEngine)));
	}

	/*
	for (int i = 0; i < 100; i++) {
		bullets.push_back(new Bullet(-10.0, -10.0, -10.0, new XMFLOAT3(0,0,0)));
	}

	for(int i = 0; i < 1; i++){
		enemies.push_back(new Enemy( 
			spacer,
			XMFLOAT3(0,0,0)
		));
	}
	*/
	skybox = new Skybox();
	sceneMgr->Insert(skybox);


	resourceMgr->md3dImmediateContext->RSSetState(0);

	resourceMgr->camera.SetPosition(XMFLOAT3(0.0f, 0.0f, -10.0f));
}

void TestState::Cleanup() {
	for(auto it = sceneMgr->Begin(); it != sceneMgr->End(); ++it) {
		delete *it;
	}
}


void TestState::Update(float dt) {
	//spacer->Update(dt);

	//int dx = currentmouseposition[0] - ( screenWidth * 0.5 );

	//int dx = input->getMouseX() - ( screenWidth * 0.5 );
	//resourceMgr->camera.RotateY( (dx / ( screenWidth * 0.5 )) * dt );

	//int dy = currentmouseposition[1] - ( screenHeight * 0.5 );
	//int dy = input->getMouseY() - ( screenHeight * 0.5 );
	//resourceMgr->camera.Pitch( (dy / ( screenHeight * 0.5 )) * dt);
	/*if (spacer->getPlayerControls()->getFired())
	{
		if(bullets.size() > 0)
		{
			fired.push_back(bullets.back());
			fired.back()->getTransform()->position = spacer->transform->position;
			fired.back()->setForward(spacer->getPhysics()->forwardAxis);
			bullets.pop_back();
			spacer->getPlayerControls()->setFired(false);
			spacer->getPlayerControls()->setFireDelay(1.0);
		}
	}*/

	XMFLOAT3 pos    = resourceMgr->camera.GetPosition( );
	XMFLOAT3 target = XMFLOAT3(0, 0, 0);
	XMFLOAT3 up     = XMFLOAT3(0.0f, 1.0f, 0.0f);

	//resourceMgr->camera.LookAt(pos, target, up);

	resourceMgr->camera.UpdateViewMatrix();

	for(auto it = sceneMgr->Begin(); it != sceneMgr->End(); ++it) {
		if(!(*it)->active)
			continue;
		(*it)->Update(dt);
	}

	/*for(auto it = fired.begin(); it != fired.end(); ++it){
		(*it)->Update(dt);
	}

	for(auto it = enemies.begin(); it != enemies.end(); ++it) {
		(*it)->Update(dt);
	}*/


	/*if( spacer != 0 )
		spacer->Update(dt);*/
	skybox->GameObject::transform->position = resourceMgr->camera.GetPosition();

	resourceMgr->updateShaderBuffers();

	//lastmouseposition[0] = currentmouseposition[0];
	//lastmouseposition[1] = currentmouseposition[1];

}

void TestState::Draw() {
	for(auto it = asteroids.begin(); it != asteroids.end(); ++it) {
		if(!(*it)->active)
			continue;
		(*it)->fillInstanceData(asteroidDraw->instances);
	}
	asteroidDraw->setEffectTextures();
	asteroidDraw->drawInstanced(asteroids.size());

	for(auto it = sceneMgr->Begin(); it != sceneMgr->End(); ++it) {
		if(!(*it)->active)
			continue;
		(*it)->Draw();
	}

	/*for(auto it = fired.begin(); it != fired.end(); ++it) {
		(*it)->Draw();
	}

	if( spacer != 0 )
		spacer->Draw();
	*/
}


void TestState::OnMouseDown(int x, int y) {
	/*cout << "mouse down" << endl;
	mouseDown = true;

	cout << resourceMgr->camera.GetPosition().z << endl;*/
}

void TestState::OnMouseUp(int x, int y) {
	/*cout << "mouse up" << endl;
	mouseDown = false;*/
}

void TestState::OnMouseMove(int x, int y) {
	//currentmouseposition[0] = x;
	//currentmouseposition[1] = y;
}
