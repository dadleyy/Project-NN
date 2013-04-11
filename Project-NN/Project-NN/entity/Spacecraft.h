#pragma once

#include "GameObject.h"

class Transform;
class Drawable;
class PlayerControls;
class PhysicsComponent;
struct ID3D11Device;
struct ID3D11DeviceContext;

class Spacecraft : public GameObject {
public:
    Spacecraft(ID3D11Device* device, ID3D11DeviceContext* immediateContext, float xPos, float yPos, float zPos);
    virtual ~Spacecraft();
    void Draw();

private:
	Transform* transform;
    Drawable* drawable;
	PlayerControls* playerControls;
	PhysicsComponent* physics;
};

