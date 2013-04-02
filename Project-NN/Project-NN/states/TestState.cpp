#include "TestState.h"

#include "StateManager.h"
#include "entity/Drawable.h"
#include "entity/Asteroid.h"

#include <iostream>
#include <random>
using namespace std;

TestState TestState::instance;
extern ResourceManager* drawAtts;

void TestState::Init(StateManager* manager)
{
	GameState::Init(manager);

	uniform_real_distribution<float> distribution(-10, 10);
	
	for(int i = 0; i < 400; i++) {
		asteroids.push_back(new Asteroid(manager->GetDevice(), manager->GetContext(),
			distribution(drawAtts->randomEngine), distribution(drawAtts->randomEngine), distribution(drawAtts->randomEngine)));
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
}

void TestState::Update(float dt)
{
	XMFLOAT3 pos    = drawAtts->camera.GetPosition();
	XMFLOAT3 target = XMFLOAT3(0, 0, 0);
	XMFLOAT3 up     = XMFLOAT3(0.0f, 1.0f, 0.0f);

	drawAtts->camera.LookAt(pos, target, up);
	drawAtts->camera.UpdateViewMatrix();

	for(auto it = asteroids.begin(); it != asteroids.end(); ++it) {
		(*it)->Update(dt);
	}
}

void TestState::Draw()
{
	for(auto it = asteroids.begin(); it != asteroids.end(); ++it) {
		(*it)->Draw();
	}
}

void TestState::OnMouseDown(int x, int y)
{
	cout << "You clicked in the game!" << endl;
	drawAtts->camera.Walk(-0.1f);
	drawAtts->camera.Strafe(0.1f);
	cout << drawAtts->camera.GetPosition().z << endl;
}