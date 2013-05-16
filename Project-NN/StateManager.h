#pragma once
#include <functional>
#include <vector>

class GameState;

class StateManager {
public:
	StateManager();
	~StateManager();

	void Init(GameState* state);
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
	
	//TODO: Refactor if time permits
	static int ToGamePlay( StateManager* manager );
	static int ToCredits( StateManager* manager );
	static int ToMainMenu( StateManager* manager );
	static int ToInstructions( StateManager* manager );
	static int Blank( StateManager* manager);
	static int ExitGame( StateManager* manager);

private:
	std::vector<GameState*> states;
	std::function<void()> preparedStateOperation;
	float wait_time;
};

