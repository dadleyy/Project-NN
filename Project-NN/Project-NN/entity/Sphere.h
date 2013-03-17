#pragma once
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include "math.h" 
#include "Drawable.h"

class Sphere : public Drawable
{
public:
	Sphere(void);
	~Sphere(void);

	Sphere(ID3D11Device* device, ID3D11DeviceContext* immediateContext);

	XMFLOAT3* getVerts(float radius, int divisions);

	virtual void createBuffer();
};

