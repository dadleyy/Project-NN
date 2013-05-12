#pragma once

class StateManager;

class GameState
{
public:
	virtual void Init(StateManager* manager);
	virtual void Cleanup() = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;
	//If a state is a substate, it is drawn on top of other states
	virtual bool IsSubState() = 0;

protected:
	StateManager* manager;
};

