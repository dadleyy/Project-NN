#include "Component.h"

class GameObject;

class ExplodeOnContact : public Component {
public:
	ExplodeOnContact(float power);
	bool Init(GameObject* go);
	void HandleCollision(GameObject* other);
private:
	float power;
	GameObject* go;
};