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
	sphere->createBuffer();
	cout << "Initting" << endl;
}

void TestState::Cleanup()
{
	sphere->destroy();
}

void TestState::Update(float dt)
{
	cout << "Updating: " << dt << endl;
}

void TestState::Draw()
{
	cout << "Drawing" << endl;
	sphere->draw();
}