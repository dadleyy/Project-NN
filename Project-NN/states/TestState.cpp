#include "TestState.h"

#include <iostream>
#include <random>
#include <unordered_set>

#include "StateManager.h"
#include "entity/BulletManager.h"
#include "entity/Drawable.h"
#include "entity/Drawables/DrawLasers.h"
#include "entity/Drawables/DrawableInstancedModel.h"
#include "entity/Asteroid.h"
#include "entity/Bomb.h"
#include "entity/Enemy.h"
#include "entity/Bullet.h"
#include "entity/Spacecraft.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "entity/Transform.h"
#include "entity/Skybox.h"
#include "../res/post processes/Glow.h"


using namespace std;

TestState TestState::instance;


void TestState::Init(StateManager* manager) {
	GameState::Init(manager);

	auto spacer = new Spacecraft(0.0, 0.0, 0.0);
	bManager = spacer->getBullets();
	sceneMgr->Insert(spacer);

	asteroidDraw = new DrawableInstancedModel();
	asteroidDraw->getEffectVariables("bumpInstancePhong", "Render");
	asteroidDraw->setShader("bumpInstancePhong", "Render");
	asteroidDraw->createBuffer("Asteroid");
	asteroidDraw->addTexture("asteroid", "diffuseMap");
	asteroidDraw->addTexture("asteroidBump", "bumpMap");
	

	glow = new Glow();
	glow->getEffectVariables("glowEffect", "Horz");
	glow->getEffectVariables("glowEffect", "Vert");
	glow->getEffectVariables("glowEffect", "Add");
	glow->setShader("glowEffect", "Horz");
	glow->createBuffer("rectangle");

	laserDraw = new DrawLasers();
	laserDraw->getEffectVariables("laserEffect", "RenderLasers");
	laserDraw->getEffectVariables("glowDraw", "RenderGlowy");

	laserDraw->setShader("glowDraw", "RenderGlowy");
	laserDraw->addEffectVariables("glowColor", "color", laserDraw->glowColor);
	laserDraw->addEffectVariables("glowColorMode", "colorMode", &laserDraw->glowMode);

	laserDraw->setShader("laserEffect", "RenderLasers");
	laserDraw->addEffectVariables("laserColor", "color", laserDraw->laserColor);
	laserDraw->createBuffer();

	uniform_real_distribution<float> distribution(-50, 50);


	for(int i = 0; i < 50; i++) {
		auto bullet = new Bullet(bManager);
		bullet->laserDraw = laserDraw;
		sceneMgr->Insert(bullet);
	}

	for(int i = 0; i < 30; i++) {
		auto asteroid = new Asteroid(distribution(resourceMgr->randomEngine), distribution(resourceMgr->randomEngine), distribution(resourceMgr->randomEngine), &asteroids);
		sceneMgr->Insert(asteroid);
		asteroids.push_back(asteroid);
	}

	uniform_real_distribution<float> enemy_d(-20, 20);
	for(int i = 0; i < 0; i++){
		float x = enemy_d(resourceMgr->randomEngine), 
			y = enemy_d(resourceMgr->randomEngine), 
			z = enemy_d(resourceMgr->randomEngine);

		auto enemy = new Enemy( spacer, XMFLOAT3(x,y,z) );
		sceneMgr->Insert( enemy );
	}

	uniform_real_distribution<float> bombDistribution(-30, 30);

	for(int i = 0; i < 2; i++) {
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

	laserDraw->setShader("laserEffect", "RenderLasers");
	laserDraw->draw();

	//draw glowy stuff
	resourceMgr->md3dImmediateContext->RSSetViewports(1, &resourceMgr->viewports["DScale2"]);
	resourceMgr->md3dImmediateContext->OMSetRenderTargets(1, &resourceMgr->renderTargets["DScale2"], NULL);
	resourceMgr->md3dImmediateContext->ClearRenderTargetView(resourceMgr->renderTargets["DScale2"], reinterpret_cast<const float*>(&Colors::Black));
	for(auto it = sceneMgr->Begin(); it != sceneMgr->End(); ++it) 
	{
		if(!(*it)->glow)
			continue;
		Drawable* temp = (*it)->GetComponent<Drawable>();
		if(temp)
		{
			temp->setShader("glowDraw", "RenderGlowy");
			temp->setEffectVariables();
			temp->setEffectTextures();
			(*it)->Draw();
			temp->setShader("betterPhong", "Render");
		}
	}
	laserDraw->setShader("glowDraw", "RenderGlowy");
	laserDraw->setEffectVariables();
	laserDraw->draw();
	laserDraw->points.clear();

	resourceMgr->md3dImmediateContext->RSSetViewports(1, &resourceMgr->viewports["Original"]);
	glow->setEffectVariables();
	glow->draw("DScale2", "Pass1", "Pass2", "Original");
}
