#pragma once

#include "entity/Component.h"

class GameObject;

/**
 * Prints a message when a collision occurs.
 */
class PrintUponCollision : public Component {
public:
	void HandleCollision(GameObject* other);
};
