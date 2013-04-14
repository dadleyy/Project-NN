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
	void Init(GameObject* go);
	void Update(float dt);

private:
	PhysicsComponent* physics;

	void handleKey( int keycode, float dt );
};
