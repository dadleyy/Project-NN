#include "TestState.h"

#include "../StateManager.h"
#include "../entity/Drawable.h"
#include "../entity/Sphere.h"

#include <iostream>
using namespace std;

TestState TestState::instance;

void TestState::Init(StateManager* manager)
{
	GameState::Init(manager);
	
    sphere = new Sphere(manager->GetDevice(), manager->GetContext());
    sphere->getEffectVariables("sphereEffect", "Render");
	sphere->createBuffer();

	cout << "Initting" << endl;
}

void TestState::Cleanup()
{
	sphere->destroy();
}

void TestState::Update(float dt)
{
}

void TestState::Draw()
{
	sphere->draw();
}

void TestState::OnMouseDown(int x, int y)
{
	cout << "You clicked in the game!" << endl;
}