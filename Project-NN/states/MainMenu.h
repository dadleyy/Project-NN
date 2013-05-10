#pragma once

#include "GameState.h"

class StateManager;

class MainMenu : public GameState {
public:
	void Init(StateManager* manager);
	void Cleanup();
	void Update(float dt);
	void Draw();

	static MainMenu* Instance() {
		return &instance;
	}
private:
	static MainMenu instance;
};