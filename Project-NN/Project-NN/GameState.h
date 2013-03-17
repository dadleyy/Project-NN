#pragma once
class GameState
{
public:
	virtual void Init() = 0;
	virtual void Cleanup() = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;
};

