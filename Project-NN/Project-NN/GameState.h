#pragma once

class StateManager;

class GameState
{
public:
	virtual void Init(StateManager* manager);
	virtual void Cleanup() = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;

	virtual void OnMouseDown(int x, int y) = 0;
    virtual void OnMouseUp(int x, int y) = 0;
    virtual void OnMouseMove(int x, int y) = 0;

protected:
	StateManager* manager;
};

