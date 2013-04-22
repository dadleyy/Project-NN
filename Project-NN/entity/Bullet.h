#pragma once

#include "GameObject.h"

class Collider;
class Drawable;
class PrintUponCollision;
class Transform;

class Bullet : public GameObject {
public:
	Bullet(float xPos, float yPos, float zPos);
	virtual ~Bullet();
	void Draw();

	Transform* getTransform(){
		return transform;
	}
private:
	Drawable* sphere;
	//Collider* collider;
	PrintUponCollision* print;
	Transform* transform;
};