#pragma once

#include "entity/Component.h"

class GameObject;
class Drawable;
class PhysicsComponent;

extern int screenWidth;
extern int screenHeight;

/**
 * Adds spaceship controls to the GameObject with this attached to it.
 *
 * Requires the Drawable component.
 */
class PlayerControls : public Component {
public:
	bool Init(GameObject* go);
	void Update(float dt);

	float relMouseX;
	float relMouseY;

	void setFireDelay(float gDelay)
	{
		fireDelay = gDelay;
	}
	bool getFired(){
		return fired;
	}

	void setFired(bool gFired){
		fired = gFired;
	}

private:
	PhysicsComponent* physics;
	bool fired;
	void handleKey( int keycode, float dt );
	float fireDelay;
};
