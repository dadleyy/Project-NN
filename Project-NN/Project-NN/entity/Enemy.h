#pragma once

#include "GameObject.h"
#include "..\framework\MathHelper.h"

class Transform;
class Drawable;
class PhysicsComponent;
class AIComponent;

struct ID3D11Device;
struct ID3D11DeviceContext;

class Enemy : public GameObject {
public:
	Enemy(ID3D11Device* device, ID3D11DeviceContext* immediateContext, GameObject* initialTarget, XMFLOAT3 intialPosition );
	virtual ~Enemy();
	void Draw();

private:
	Transform* transform;
	Drawable* drawable;
	AIComponent* ai;
	PhysicsComponent* physics;
};

