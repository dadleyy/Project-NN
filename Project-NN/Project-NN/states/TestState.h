#pragma once
#include "../GameState.h"

class TestState : GameState
{
public:
	TestState();
	virtual ~TestState(void);

	virtual void Update(float dt);
	virtual void Draw();
};