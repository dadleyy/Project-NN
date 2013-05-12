#pragma once

#include "GameState.h"

class StateManager;

class Pause : public GameState {
public:
	void Init(StateManager* manager);
	void Cleanup();
	void Update(float dt);
	void Draw();

	static Pause* Instance() {
		return &instance;
	}
	bool IsSubState() {
		return true;
	}
private:
	static Pause instance;
};
