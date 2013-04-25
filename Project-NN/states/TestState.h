#pragma once

#include <vector>

#include "GameState.h"


class StateManager;
class Asteroid;
class Spacecraft;
class Enemy;
class DrawableInstancedModel;
class Bomb;
class Bullet;
class Skybox;

extern int screenWidth;
extern int screenHeight;

class TestState : public GameState {
public:

	void Init(StateManager* manager);
	void Cleanup();
	void Update(float dt);
	void Draw();
	void OnMouseDown(int x, int y);
	void OnMouseUp(int x, int y);
	void OnMouseMove(int x, int y);

	static TestState* Instance() {
		return &instance;
	}

private:

	void handleKey( int keycode, float dt );

	static TestState instance;
	std::vector<Asteroid*> asteroids;
	std::vector<Enemy*> enemies;
	std::vector<Bomb*> bombs;
	std::vector<Bullet*> bullets;
	std::vector<Bullet*> fired;
	Spacecraft* spacer;
	Skybox* skybox;

	DrawableInstancedModel* asteroidDraw;

	bool mouseDown;

	int currentmouseposition[2];
	int lastmouseposition[2];

};