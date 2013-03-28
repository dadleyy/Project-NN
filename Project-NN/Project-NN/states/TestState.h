#pragma once

#include "GameState.h"

class StateManager;
class Drawable;

class TestState : public GameState
{
public:

	void Init(StateManager* manager);
	void Cleanup();
	void Update(float dt);
	void Draw();
	void OnMouseDown(int x, int y);

	static TestState* Instance() {
		return &instance;
	}

private:
	static TestState instance;
	Drawable* sphere;

};