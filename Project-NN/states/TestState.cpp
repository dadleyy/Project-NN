#include "TestState.h"

#include <iostream>
#include <random>
#include <unordered_set>

#include "StateManager.h"
#include "entity/BulletManager.h"
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

	auto spacer = new Spacecraft(0.0, 0.0, 0.0);
	bManager = spacer->getBullets();
	sceneMgr->Insert(spacer);

	asteroidDraw = new DrawableInstancedModel();
	asteroidDraw->getEffectVariables("bumpInstancePhong", "Render");
	asteroidDraw->createBuffer("Asteroid");
	asteroidDraw->addTexture("asteroid", "diffuseMap");
	asteroidDraw->addTexture("asteroidBump", "bumpMap");

	uniform_real_distribution<float> distribution(-50, 50);


	for(int i = 0; i < 50; i++) {
		auto bullet = new Bullet(bManager);
		sceneMgr->Insert(bullet);
	}

	for(int i = 0; i < 30; i++) {
		auto asteroid = new Asteroid(distribution(resourceMgr->randomEngine), distribution(resourceMgr->randomEngine), distribution(resourceMgr->randomEngine), &asteroids);
		sceneMgr->Insert(asteroid);
		asteroids.push_back(asteroid);
	}

	uniform_real_distribution<float> enemy_d(-50, 50);
	for(int i = 0; i < 20; i++){
		float x = enemy_d(resourceMgr->randomEngine), 
			  y = enemy_d(resourceMgr->randomEngine), 
			  z = enemy_d(resourceMgr->randomEngine);

		auto enemy = new Enemy( spacer, XMFLOAT3(x,y,z) );
		sceneMgr->Insert( enemy );
	}

	uniform_real_distribution<float> bombDistribution(-30, 30);

	for(int i = 0; i < 5; i++) {
		sceneMgr->Insert(new Bomb(
			bombDistribution(resourceMgr->randomEngine),
			bombDistribution(resourceMgr->randomEngine),
			bombDistribution(resourceMgr->randomEngine)));
	}

	skybox = new Skybox();
	sceneMgr->Insert(skybox);

	resourceMgr->md3dImmediateContext->RSSetState(0);
	resourceMgr->camera.SetPosition(XMFLOAT3(0.0f, 0.0f, -10.0f));
}

void TestState::Cleanup() {
	for(auto it = sceneMgr->Begin(); it != sceneMgr->End(); ++it) {
		delete *it;
	}
	delete asteroidDraw;
}


void TestState::Update(float dt) {
	XMFLOAT3 pos    = resourceMgr->camera.GetPosition( );
	XMFLOAT3 target = XMFLOAT3(0, 0, 0);
	XMFLOAT3 up     = XMFLOAT3(0.0f, 1.0f, 0.0f);

	resourceMgr->camera.UpdateViewMatrix();

	for(auto it = sceneMgr->Begin(); it != sceneMgr->End(); ++it) {
		if(!(*it)->active)
			continue;
		(*it)->Update(dt);
	}

	skybox->GameObject::transform->position = resourceMgr->camera.GetPosition();
	resourceMgr->updateShaderBuffers();
}

void TestState::Draw() {
	int activeAsteroids = 0;
	for(auto it = asteroids.begin(); it != asteroids.end(); ++it) {
		if(!(*it)->active)
			continue;
		activeAsteroids++;
		(*it)->fillInstanceData(asteroidDraw->instances);
	}
	if(activeAsteroids > 0) {
		asteroidDraw->setEffectTextures();
		asteroidDraw->drawInstanced(activeAsteroids);
	}

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
