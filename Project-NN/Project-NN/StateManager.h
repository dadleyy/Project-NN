#pragma once

class State;

class StateManager
{
public:
	StateManager(void);
	~StateManager(void);

	void Update(float dt);
	void Draw();
	void PushState(State* state);
	void PopState();
};

