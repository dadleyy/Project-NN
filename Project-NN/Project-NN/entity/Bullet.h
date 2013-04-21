#pragma once

#include "GameObject.h"

class Collider;
class Drawable;
class PrintUponCollision;
class Transform;
//TODO: Remove -- we have this in resourceMgr
struct ID3D11Device;
struct ID3D11DeviceContext;

class Bullet : public GameObject {
public:
	Bullet(ID3D11Device* device, ID3D11DeviceContext* immediateContext, float xPos, float yPos, float zPos);
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