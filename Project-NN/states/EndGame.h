#pragma once

#include "GameState.h"

class StateManager;

class EndGame : public GameState {
public:
	void Init(StateManager* manager);
	void Cleanup();
	void Update(float dt);
	void Draw();

	static EndGame* Instance() {
		return &instance;
	}
	bool IsSubState() {
		return true;
	}
private:
	static EndGame instance;
};