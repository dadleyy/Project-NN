#pragma once

#include <vector>
#include "GameObject.h"


class Collider;
class Drawable;
class DivideOnContact;
class Transform;


class Asteroid : public GameObject {
public:
	Asteroid(float xPos, float yPos, float zPos, std::vector<Asteroid*>* asteroids);
	virtual ~Asteroid();
	GameObject* Clone();
	void fillInstanceData(std::vector<float>* data);
private:
	Collider* collider;
	DivideOnContact* divide;
	Transform* transform;
	std::vector<Asteroid*>* asteroids;
};