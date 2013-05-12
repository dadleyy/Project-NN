#pragma once
#include <vector>

class GameState;

class StateManager {
public:
	StateManager();
	~StateManager();

	void Init();
	void Update(float dt);
	void Draw();

	void OnMouseDown(int x, int y);
	void OnMouseUp(int x, int y);
	void OnMouseMove(int x, int y);
	void OnKeyUp(int keycode);
	void OnKeyDown(int keycode);

	void PushState(GameState* state);
	void PopState();

private:
	std::vector<GameState*> states;
};

