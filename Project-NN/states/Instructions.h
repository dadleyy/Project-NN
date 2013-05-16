#pragma once

#include "GameState.h"
#include <vector>

class StateManager;
class MenuItem;

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
		return false;
	}
private:
	static Instructions instance;
	MenuItem* background;
	MenuItem* backBtn;
};