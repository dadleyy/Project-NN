#include "LERP.h"
#include "quaternionMath.h"

floatLERP::floatLERP(void)
{
	lerping = 1;
	place = 0;
}


floatLERP::~floatLERP(void)
{
}

float floatLERP::lerp(float change, float rate)
{
	place += change*rate;

	float number = (1-place)*start + place*goal;

	if(number - goal < .001 || goal - number < .001)
	{
		number = goal;
		lerping = 0;
	}
	else 
		lerping = 1;

	return number;
}


float3LERP::float3LERP(void)
{
	lerping = 1;
	place = 0;
}


float3LERP::~float3LERP(void)
{
}

XMFLOAT3 float3LERP::lerp(float change, float rate)
{
	place = change*rate;

	XMFLOAT3 number = add(scale(start, (1-place)), scale(goal, place));

	/*if(abs(number.x - goal.x) < .001 && abs(number.y - goal.y) && abs(number.z - goal.z))
	{
		number = goal;
		lerping = 0;
	}*/
	//else 
		lerping = 1;

	return number;
}
