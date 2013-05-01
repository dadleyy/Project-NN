#pragma once

#include "GameObject.h"

class Transform;
class Drawable;
class PlayerControls;
class PhysicsComponent;
class PlayerCameraComponent;
class BulletManager;

class Spacecraft : public GameObject {
public:
    Spacecraft(float xPos, float yPos, float zPos);
    void Draw();

	PlayerControls* getPlayerControls(){
		return playerControls;
	}
	PhysicsComponent* getPhysics(){
		return physics;
	}
	BulletManager* getBullets(){
		return bManager;
	}
private:
	BulletManager* bManager;
    Drawable* drawable;
	PlayerCameraComponent* playerCamera;
	PlayerControls* playerControls;
	PhysicsComponent* physics;
};

