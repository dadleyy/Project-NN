#pragma once

#include "math.h" 
#include "Drawable.h"

class Sphere : public Drawable
{
public:
	Sphere(void);
	~Sphere(void);

	Sphere(ID3D11Device* device, ID3D11DeviceContext* immediateContext);

	virtual void createBuffer();
	virtual XMFLOAT3* getVerts(float radius, int divisions);
	virtual UINT* getIndicies();

private:
	
};

