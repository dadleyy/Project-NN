#pragma once
#include <Windows.h>
#include <xnamath.h>

class floatLERP
{
public:
	floatLERP(void);
	~floatLERP(void);

	bool lerping;

	float goal;
	float start;
	float place;

	float lerp(float change, float rate);
	
};

class float3LERP
{
public:
	float3LERP(void);
	~float3LERP(void);

	bool lerping;

	XMFLOAT3 goal;
	XMFLOAT3 start;
	float place;

	XMFLOAT3 lerp(float change, float rate);
};

