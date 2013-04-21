#pragma once

#include "math.h" 
#include "Drawable.h"

class Sphere : public Drawable
{
public:
	Sphere();
	~Sphere();

	virtual void createBuffer();
	virtual void createBuffer(char* mesh);
	virtual XMFLOAT3* getVerts(float radius, int divisions);
	virtual UINT* getIndicies();

private:
	
};

