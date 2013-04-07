#pragma once
#include <vector>

class GameState;
struct ID3D11Device;
struct ID3D11DeviceContext;

class StateManager
{
public:
	StateManager(void);
	~StateManager(void);

	void Init(ID3D11Device* device, ID3D11DeviceContext* context);
	void Update(float dt);
	void Draw();

	void OnMouseDown(int x, int y);
    void OnMouseUp(int x, int y);
    void OnMouseMove(int x, int y);
    void OnKeyUp(int keycode);
    void OnKeyDown(int keycode);

	void PushState(GameState* state);
	void PopState();
	
	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetContext();

    bool keystates[256];

private:
	std::vector<GameState*> states;
	ID3D11Device* device;
	ID3D11DeviceContext* context;
};

