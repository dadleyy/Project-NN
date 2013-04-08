#include "Light.h"


LightStruct* createLight(float posX, float posY, float posZ,
						 float colX, float colY, float colZ, float colA,
						 float dirX, float dirY, float dirZ,
						 float radius, float angle, float intensity, int falloff, 
						 int onOff, int type)
{
	LightStruct* l = new LightStruct();

	l->position = D3DXVECTOR4(posX, posY, posZ, 0.0);
	l->color = D3DXVECTOR4(colX, colY, colZ, colA);
	l->direction = D3DXVECTOR4(dirX, dirY, dirZ, 0.0);
	l->radius = radius;
	l->angle = angle*(3.14159265359/180);
	l->falloff = falloff;
	l->onOff = onOff;
	l->type = type;
	l->intensity = intensity;

	l->padding = D3DXVECTOR2(0.0,0.0);

	return l;
}