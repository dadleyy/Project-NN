#pragma once
#include "../GameState.h"

class TestState : public GameState
{
public:

	void Init();
	void Cleanup();
	void Update(float dt);
	void Draw();

	static TestState* Instance() {
		return &instance;
	}

private:
	static TestState instance;
};