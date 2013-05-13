#pragma once

#include "GameState.h"

class StateManager;
class MenuItem;

class MainMenu : public GameState {
public:
	void Init(StateManager* manager);
	void Cleanup();
	void Update(float dt);
	void Draw();

	static MainMenu* Instance() {
		return &instance;
	}
	bool IsSubState() {
		return false;
	}
private:
	static MainMenu instance;
	MenuItem* playbutton;

};