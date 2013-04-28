#pragma once
#include "GameObject.h"

class Transform;
class Drawable;
struct ID3D11RasterizerState;

class Skybox :
	public GameObject
{
public:
	Skybox(void);
	~Skybox(void);
	void Draw();

private:
	ID3D11RasterizerState* frontCullRasterState;
	Transform* transform;
    Drawable* drawable;

};

