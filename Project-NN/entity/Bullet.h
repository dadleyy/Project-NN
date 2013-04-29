#pragma once

#include "GameObject.h"

class Collider;
class Drawable;
class PrintUponCollision;
class BulletFiring;
class Transform;

class Bullet : public GameObject {
public:
	Bullet(float xPos, float yPos, float zPos, XMFLOAT3 gForward);
	void Draw();

	Transform* getTransform(){
		return transform;
	}
	void setForward(XMFLOAT3 gForward)
	{
		forward = gForward;
	}
	int getSpeed(){
		return SPEED;
	}
	void Update(float dt);
private:
	Drawable* sphere;
	//Collider* collider;
	static const int SPEED = 1;
	XMFLOAT3 forward;
	PrintUponCollision* print;
	Transform* transform;
	BulletFiring* fireBullet;
};