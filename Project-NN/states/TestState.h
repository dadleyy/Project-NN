#pragma once

#include <vector>

#include "GameState.h"


class StateManager;
class Asteroid;
class Spacecraft;
class BulletManager;
class Enemy;
class DrawableInstancedModel;
class Bomb;
class Bullet;
class Skybox;
class Glow;

extern int screenWidth;
extern int screenHeight;

class TestState : public GameState {
public:

	void Init(StateManager* manager);
	void Cleanup();
	void Update(float dt);
	void Draw();

	static TestState* Instance() {
		return &instance;
	}

private:
	static TestState instance;

	BulletManager* bManager;
	std::vector<Asteroid*> asteroids;

	DrawableInstancedModel* asteroidDraw;
	Glow* glow;

	Skybox* skybox;
};