#pragma once

#include <vector>
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
		return &mainmenu_instance;
	}
	bool IsSubState() {
		return false;
	}
private:
	static MainMenu mainmenu_instance;
	std::vector<MenuItem*> buttons;

	MenuItem* menuBG;

};