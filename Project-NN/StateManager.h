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

	void ChangeState(GameState* state);
	void PushState(GameState* state);
	void PopState();
	
	static int ToGamePlay( StateManager* manager );
	static int ToCredits( StateManager* manager );
	static int ToMainMenu( StateManager* manager );
	static int Blank( StateManager* manager);

private:
	std::vector<GameState*> states;
	float wait_time;
};

