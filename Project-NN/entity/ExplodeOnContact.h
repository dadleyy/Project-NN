#include "Component.h"

class GameObject;

class ExplodeOnContact : public Component {
public:
	ExplodeOnContact(float power);
	void HandleCollision(GameObject* other);
private:
	float power;
};