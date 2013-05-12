#pragma once

#include "GameState.h"

class StateManager;

class Instructions : public GameState {
public:
	void Init(StateManager* manager);
	void Cleanup();
	void Update(float dt);
	void Draw();

	static Instructions* Instance() {
		return &instance;
	}
	bool IsSubState() {
		return true;
	}
private:
	static Instructions instance;
};