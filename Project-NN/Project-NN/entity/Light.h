#pragma once
#include <d3d10.h>
#include <d3dx10.h>
#include <vector>

using std::vector;

enum LightType {AMBIENT_LIGHT, DIRECTIONAL_LIGHT, POINT_LIGHT, SPOT_LIGHT};
enum FallOffType {NONE, LINEAR, QUADRATIC};

struct LightStruct
{
	D3DXVECTOR4 position;	//POINT : SPOT
	D3DXVECTOR4 color;		//DIR : POINT : SPOT : AMBIENT
	D3DXVECTOR4 direction;	//DIR : SPOT
	float radius;			//POINT : SPOT
	float angle;			//SPOT
	float intensity;		//DIR : POINT : SPOT : AMBIENT
	int falloff;			//POINT : SPOT
	int onOff;				//DIR : POINT : SPOT
	int type;				//DIR : POINT : SPOT
	D3DXVECTOR2 padding;
};



LightStruct* createLight(float posX, float posY, float posZ,
							  float colX, float colY, float colZ, float colA,
							  float dirX, float dirY, float dirZ,
							  float radius, float angle, float intensity, int falloff, 
							  int onOff, int type);