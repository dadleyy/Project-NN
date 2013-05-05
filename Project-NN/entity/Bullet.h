#pragma once

#include <vector>
#include "GameObject.h"


class Collider;
class Drawable;
class PrintUponCollision;
class BulletFiring;
class BulletManager;
class Transform;

class Bullet : public GameObject {
public:
	Bullet(BulletManager* gManager);
	Bullet(float xPos, float yPos, float zPos, XMFLOAT3 gForward);
	void Draw();

	Transform* getTransform(){
		return transform;
	}
	void setForward(XMFLOAT3 gForward)
	{
		forward = gForward;
	}
	void Update(float dt);
	
	
	Transform* transform;
	static const int SPEED = 5;
	XMFLOAT3 forward;

private:
	Drawable* sphere;
	Collider* collider;
	BulletManager* manager;
	PrintUponCollision* print;
	BulletFiring* fireBullet;
};