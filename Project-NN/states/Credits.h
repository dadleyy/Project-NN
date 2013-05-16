#pragma once

#include <vector>
#include "GameState.h"

class StateManager;
class MenuItem;

class Credits : public GameState {
public:
	void Init(StateManager* manager);
	void Cleanup();
	void Update(float dt);
	void Draw();

	static Credits* Instance() {
		return &credits_instace;
	}
	bool IsSubState() {
		return false;
	}
private:
	static Credits credits_instace;
	
	std::vector<MenuItem*> statics;
	std::vector<MenuItem*> buttons;

};