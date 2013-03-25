#include "TestState.h"

#include "../StateManager.h"
#include "../entity/Drawable.h"
#include "../entity/Sphere.h"

#include <iostream>
using namespace std;

TestState TestState::instance;
extern ResourceManager* drawAtts;

void TestState::Init(StateManager* manager)
{
	GameState::Init(manager);
	
    sphere = new Sphere(manager->GetDevice(), manager->GetContext());
    sphere->getEffectVariables("sphereEffect", "Render");
	sphere->createBuffer();

	cout << "Initting" << endl;
	drawAtts->camera.SetPosition(XMFLOAT3(-0.3f, -0.3f, -0.3f));
}

void TestState::Cleanup()
{
	sphere->destroy();
}

void TestState::Update(float dt)
{
	XMFLOAT3 pos    = drawAtts->camera.GetPosition();
	XMFLOAT3 target = XMFLOAT3(0, 0, 0);
	XMFLOAT3 up     = XMFLOAT3(0.0f, 1.0f, 0.0f);

	drawAtts->camera.LookAt(pos, target, up);
	drawAtts->camera.UpdateViewMatrix();
}

void TestState::Draw()
{
	sphere->draw();
}

void TestState::OnMouseDown(int x, int y)
{
	cout << "You clicked in the game!" << endl;
	drawAtts->camera.Walk(-0.1f);
	drawAtts->camera.Strafe(0.1f);
	cout << drawAtts->camera.GetPosition().z << endl;
}