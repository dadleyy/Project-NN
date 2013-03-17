#pragma once
#include "../GameState.h"

class StateManager;

class TestState : public GameState
{
public:

	void Init(StateManager* manager);
	void Cleanup();
	void Update(float dt);
	void Draw();

	static TestState* Instance() {
		return &instance;
	}

private:
	static TestState instance;
};