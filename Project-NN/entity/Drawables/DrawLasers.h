#pragma once
#include "../Drawable.h"

class DrawLasers : public Drawable
{
public:
	DrawLasers(void);
	~DrawLasers(void);

	ID3D11Buffer* vertexBuffer;
	virtual void createBuffer();
	virtual void draw();
	std::vector<XMFLOAT3> points;
	float glowColor[4];
	float laserColor[4];
	float glowMode;
};

