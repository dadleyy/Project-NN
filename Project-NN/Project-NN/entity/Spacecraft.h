#pragma once

#include "GameObject.h"

class Transform;
class Drawable;
class PlayerControls;
class PhysicsComponent;
class PlayerCameraComponent;

class Spacecraft : public GameObject {
public:
    Spacecraft(float xPos, float yPos, float zPos);
    virtual ~Spacecraft();
    void Draw();

	PlayerControls* getPlayerControls(){
		return playerControls;
	}
private:
	Transform* transform;
    Drawable* drawable;
	PlayerCameraComponent* playerCamera;
	PlayerControls* playerControls;
	PhysicsComponent* physics;
};

