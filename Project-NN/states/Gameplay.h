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
class DrawLasers;

extern int screenWidth;
extern int screenHeight;

class Gameplay : public GameState {
public:

	void Init(StateManager* manager);
	void Cleanup();
	void Update(float dt);
	void Draw();

	static Gameplay* Instance() {
		return &instance;
	}
	bool IsSubState() {
		return false;
	}

private:
	static Gameplay instance;

	BulletManager* bManager;
	std::vector<Asteroid*> asteroids;

	DrawableInstancedModel* asteroidDraw;
	Glow* glow;
	DrawLasers* laserDraw;

	Skybox* skybox;
};