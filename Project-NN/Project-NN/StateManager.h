#pragma once
#include <vector>

class GameState;

class StateManager
{
public:
	StateManager(void);
	~StateManager(void);

	void Update(float dt);
	void Draw();
	void PushState(GameState* state);
	void PopState();

private:
	std::vector<GameState*> states;
};

