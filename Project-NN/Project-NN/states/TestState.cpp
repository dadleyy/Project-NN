#include "TestState.h"

#include "StateManager.h"
#include "entity/Drawable.h"
#include "entity/Asteroid.h"

#include <iostream>
using namespace std;

TestState TestState::instance;
extern ResourceManager* drawAtts;

void TestState::Init(StateManager* manager)
{
	GameState::Init(manager);
	
	asteroid = new Asteroid(manager->GetDevice(), manager->GetContext());

	cout << "Initting" << endl;
	drawAtts->camera.SetLens(0.25f*MathHelper::Pi, 800.0/600.0f, 0.01f, 100.0f);
	drawAtts->camera.SetPosition(XMFLOAT3(0.5f, 0.5f, -1.0f));
}

void TestState::Cleanup()
{
}

void TestState::Update(float dt)
{
	XMFLOAT3 pos    = drawAtts->camera.GetPosition();
	XMFLOAT3 target = XMFLOAT3(0, 0, 0);
	XMFLOAT3 up     = XMFLOAT3(0.0f, 1.0f, 0.0f);

	drawAtts->camera.LookAt(pos, target, up);
	drawAtts->camera.UpdateViewMatrix();

	asteroid->Update(dt);
}

void TestState::Draw()
{
	asteroid->Draw();
}

void TestState::OnMouseDown(int x, int y)
{
	cout << "You clicked in the game!" << endl;
	drawAtts->camera.Walk(-0.1f);
	drawAtts->camera.Strafe(0.1f);
	cout << drawAtts->camera.GetPosition().z << endl;
}