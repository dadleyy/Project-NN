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
    virtual ~Spacecraft();
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
	//Transform* transform;
	BulletManager* bManager;
    Drawable* drawable;
	Collider* collider;
	PlayerCameraComponent* playerCamera;
	PlayerControls* playerControls;
	PhysicsComponent* physics;
};

