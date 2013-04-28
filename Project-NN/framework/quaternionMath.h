#pragma once

#include <math.h>
#include <Windows.h>
#include <xnamath.h>

#define PI		 3.1415926535899f
#define PI2		 6.2831853071796f
#define RADDEG	  .0174562925199f
#define DEGRAD	57.2957795130823f

//***************************************
//Commonly used linear constructs
//Vectors and Points assumed homogenous
//i.e. Point 2 = x, y, w
///**************************************

struct Mat4
{
	Mat4() {x[0] = 1; x[1] = 0; x[2] = 0; x[3] = 0;
			y[0] = 0; y[1] = 1; y[2] = 0; y[3] = 0;
			z[0] = 0; z[1] = 0; z[2] = 1; z[3] = 0;
			w[0] = 0; w[1] = 0; w[2] = 0; w[3] = 1;}
	Mat4(float *xArray, float *yArray, float *zArray, float *wArray) 
			{x[0] = xArray[0]; x[1] = xArray[1]; x[2] = xArray[2]; x[3] = xArray[3];
			 y[0] = yArray[0]; y[1] = yArray[1]; y[2] = yArray[2]; y[3] = yArray[3];
			 z[0] = zArray[0]; z[1] = zArray[1]; z[2] = zArray[2]; z[3] = zArray[3];
			 w[0] = wArray[0]; w[1] = wArray[1]; w[2] = wArray[2]; w[3] = wArray[3];}
	Mat4(float x1, float x2, float x3, float x4,
		 float y1, float y2, float y3, float y4,
		 float z1, float z2, float z3, float z4,
		 float w1, float w2, float w3, float w4) 
			{x[0] = x1; x[1] = x2; x[2] = x3; x[3] = x4;
			 y[0] = y1; y[1] = y2; y[2] = y3; y[3] = y4;
			 z[0] = z1; z[1] = z2; z[2] = z3; z[3] = z4;
			 w[0] = w1; w[1] = w2; w[2] = w3; w[3] = w4;}
	float* toArray();
	void toArray(float* a);
	float x[4];
	float y[4];
	float z[4];
	float w[4];
};

struct Quaternion
{
	Quaternion(){w = 1; x = 0; y = 0; z = 0;};
	Quaternion(float degrees, XMFLOAT3 v)
	{
		float k = (degrees*RADDEG)/2;
		w = cos(k); x = v.x*sin(k); y = v.y*sin(k); z = v.z*sin(k);
	};
	Quaternion(float angle, float v, float r, float t)
	{
		w = angle; x = v; y = r; z = t;
	};
	//sends the quaternion to an array
	void toArray(float* a);
	Mat4 toMatrix();
	float* toArray();
	float x;
	float y;
	float z;
	float w;
};


int sign(float x);
Mat4 transpose(Mat4 m);


XMFLOAT3 add(XMFLOAT3 v1, XMFLOAT3 v2);


//*******************************
//Multiplication*
//*******************************
Mat4 mult(Mat4 m1, Mat4 m2);
Quaternion mult(Quaternion q1, Quaternion q2);


//*******************************
//Scaling
//*******************************
void scale(Mat4* m, float s);
Quaternion scale(Quaternion q, float s);
void scale(Quaternion* q, float s);
XMFLOAT3 scale(XMFLOAT3 v, float s);

//*******************************
//Dot Product and Cross Product*
//*******************************
float dotProduct(Quaternion q1, Quaternion q2);
float dotProduct(XMFLOAT3 q1, XMFLOAT3 q2);

//***************************
//Normalization*
//***************************
Quaternion normalize(Quaternion q);


//***************************
//Magnitudes*
//***************************
float magnitude(Quaternion q);
float magnitudeSq(Quaternion q);

//****************************
//Interpolations
//****************************
Quaternion slerp(Quaternion q1, Quaternion q2, float t); 
Quaternion nLerp(Quaternion q1, Quaternion q2, float t); 


Quaternion conjugate(Quaternion q);

XMFLOAT3 transformVector(Quaternion q, XMFLOAT3 v);
Quaternion toQuatFromXMFloat3( XMFLOAT3 v );