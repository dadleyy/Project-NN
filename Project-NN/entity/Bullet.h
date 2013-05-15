#pragma once

#include <vector>
#include "GameObject.h"


class Collider;
class DrawLasers;
class PrintUponCollision;
class BulletFiring;
class BulletManager;
class Transform;
class PhysicsComponent;

class Bullet : public GameObject {
public:
	Bullet(BulletManager* gManager);
	Bullet(float xPos, float yPos, float zPos, XMFLOAT3 gForward);
	void Draw();

	void Update(float dt);
	
	const float SPEED;
	XMFLOAT3 forward;
	DrawLasers* laserDraw;

private:
	Collider* collider;
	BulletManager* manager;
	PrintUponCollision* print;
	BulletFiring* fireBullet;
	PhysicsComponent* physics;
};