#include "TestState.h"

#include <iostream>
using namespace std;

TestState TestState::instance;

void TestState::Init()
{
	cout << "Initting" << endl;
}

void TestState::Cleanup()
{
}

void TestState::Update(float dt)
{
	cout << "Updating: " << dt << endl;
}

void TestState::Draw()
{
	cout << "Drawing" << endl;
}