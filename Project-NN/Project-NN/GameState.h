#pragma once
class GameState
{
public:
	GameState();
	virtual ~GameState(void);

	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;
};

