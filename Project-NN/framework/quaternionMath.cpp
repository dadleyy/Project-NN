#include "quaternionMath.h"


//****************************************
//Sends the values to an array
//****************************************
void Quaternion::toArray(float* a)
{
	a[0] = x; a[1] = y;	a[2] = z; a[3] = w;
}
Mat4 Quaternion::toMatrix()
{
	float qpx = 2*pow(x,2);
	float qpy = 2*pow(y,2);
	float qpz = 2*pow(z,2);
	float qTx = 2*x;
	float qTw = 2*w;
	float qTy = 2*y;

	Mat4 quatMat(1-qpy-qpz,			qTx*y-qTw*z,		qTx*z+qTw*y,		0,
				qTx*y+qTw*z,		1-qpx-qpz,			qTy*z-qTw*x,		0,
				qTx*z-qTw*y,		qTy*z+qTw*x,		1-qpx-qpy,			0,
					0,					0,					0,				1);

	return quatMat;
}

float* Quaternion::toArray()
{
	float a[4];
	a[0] = x; a[1] = y;	a[2] = z; a[3] = w;
	return a;
}

XMFLOAT3 add( XMFLOAT3 v1, XMFLOAT3 v2 )
{
	return XMFLOAT3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

void Mat4::toArray(float* a)
{
	a[0] = x[0];  a[1] = x[1];	 a[2] = x[2];	a[3] = x[3];
	a[4] = y[0];  a[5] = y[1];	 a[6] = y[2];	a[7] = y[3];
	a[8] = z[0];  a[9] = z[1];	 a[10]= z[2];	a[11]= z[3];
	a[12]= w[0];  a[13]= w[1];	 a[14]= w[2];	a[15]= w[3];
}
float* Mat4::toArray()
{
	float a[16];
	a[0] = x[0];  a[1] = x[1];	 a[2] = x[2];	a[3] = x[3];
	a[4] = y[0];  a[5] = y[1];	 a[6] = y[2];	a[7] = y[3];
	a[8] = z[0];  a[9] = z[1];	 a[10]= z[2];	a[11]= z[3];
	a[12]= w[0];  a[13]= w[1];	 a[14]= w[2];	a[15]= w[3];
	return a;
}

int sign(float x)
{
	if(x >= 0)
		return 1;
	
	return -1;
}

Mat4 transpose(Mat4 m)
{
	Mat4 m1 = Mat4(m.x[0], m.y[0], m.z[0], m.w[0], 
				   m.x[1], m.y[1], m.z[1], m.w[1], 
				   m.x[2], m.y[2], m.z[2], m.w[2], 
				   m.x[3], m.y[3], m.z[3], m.w[3]);
	return m1;
}

//multiplies m1*m2
Mat4 mult(Mat4 m1, Mat4 m2)
{
	Mat4 m;

	m.x[0] = m1.x[0]*m2.x[0] + m1.x[1]*m2.y[0] + m1.x[2]*m2.z[0] + m1.x[3]*m2.w[0];
	m.x[1] = m1.x[0]*m2.x[1] + m1.x[1]*m2.y[1] + m1.x[2]*m2.z[1] + m1.x[3]*m2.w[1];
	m.x[2] = m1.x[0]*m2.x[2] + m1.x[1]*m2.y[2] + m1.x[2]*m2.z[2] + m1.x[3]*m2.w[2];
	m.x[3] = m1.x[0]*m2.x[3] + m1.x[1]*m2.y[3] + m1.x[2]*m2.z[3] + m1.x[3]*m2.w[3];

	m.y[0] = m1.y[0]*m2.x[0] + m1.y[1]*m2.y[0] + m1.y[2]*m2.z[0] + m1.y[3]*m2.w[0];
	m.y[1] = m1.y[0]*m2.x[1] + m1.y[1]*m2.y[1] + m1.y[2]*m2.z[1] + m1.y[3]*m2.w[1];
	m.y[2] = m1.y[0]*m2.x[2] + m1.y[1]*m2.y[2] + m1.y[2]*m2.z[2] + m1.y[3]*m2.w[2];
	m.y[3] = m1.y[0]*m2.x[3] + m1.y[1]*m2.y[3] + m1.y[2]*m2.z[3] + m1.y[3]*m2.w[3];

	m.z[0] = m1.z[0]*m2.x[0] + m1.z[1]*m2.y[0] + m1.z[2]*m2.z[0] + m1.z[3]*m2.w[0];
	m.z[1] = m1.z[0]*m2.x[1] + m1.z[1]*m2.y[1] + m1.z[2]*m2.z[1] + m1.z[3]*m2.w[1];
	m.z[2] = m1.z[0]*m2.x[2] + m1.z[1]*m2.y[2] + m1.z[2]*m2.z[2] + m1.z[3]*m2.w[2];
	m.z[3] = m1.z[0]*m2.x[3] + m1.z[1]*m2.y[3] + m1.z[2]*m2.z[3] + m1.z[3]*m2.w[3];

	m.w[0] = m1.w[0]*m2.x[0] + m1.w[1]*m2.y[0] + m1.w[2]*m2.z[0] + m1.w[3]*m2.w[0];
	m.w[1] = m1.w[0]*m2.x[1] + m1.w[1]*m2.y[1] + m1.w[2]*m2.z[1] + m1.w[3]*m2.w[1];
	m.w[2] = m1.w[0]*m2.x[2] + m1.w[1]*m2.y[2] + m1.w[2]*m2.z[2] + m1.w[3]*m2.w[2];
	m.w[3] = m1.w[0]*m2.x[3] + m1.w[1]*m2.y[3] + m1.w[2]*m2.z[3] + m1.w[3]*m2.w[3];

	return m;
}


//multiplies 2 quaternions
Quaternion mult(Quaternion q1, Quaternion q2)
{
	Quaternion q;

	q.w = q1.w*q2.w - q1.x*q2.x - q1.y*q2.y - q1.z*q2.z;
	q.x = q1.w*q2.x + q1.x*q2.w + q1.y*q2.z - q1.z*q2.y;
	q.y = q1.w*q2.y - q1.x*q2.z + q1.y*q2.w + q1.z*q2.x;
	q.z = q1.w*q2.z + q1.x*q2.y - q1.y*q2.x + q1.z*q2.w;

	return q;
}


//***********************
//*******************************
//Dot Product and Cross Product
//*******************************
//***********************
float dotProduct(XMFLOAT3 q1, XMFLOAT3 q2)
{ return q1.x*q2.x + q1.y*q2.y + q1.z*q2.z; }

float dotProduct(Quaternion q1, Quaternion q2)
{ return q1.x*q2.x + q1.y*q2.y + q1.z*q2.z + q1.w*q2.w; }




//***********************
//*******************************
//Magnitudes
//*******************************
//***********************
//the magnitude of a quaternion
float magnitude(Quaternion q)
{	return sqrt( pow(q.x, 2) + pow(q.y, 2) + pow(q.z, 2) + pow(q.w, 2) ); }

//The squared magnitude of a quaternion
float magnitudeSq(Quaternion q)
{	return (pow(q.x, 2) + pow(q.y, 2) + pow(q.z, 2) + pow(q.w, 2)); }


Quaternion normalize(Quaternion q)
{
	Quaternion quat = q;
	float mag = magnitudeSq(quat);

	if((mag > 1.00001 || mag < .99999) && mag != 0)
	{
		mag = sqrt(mag);
		scale(&quat, 1/mag);
	}

	return quat;
}

void normalize(Quaternion* q)
{
	float mag = magnitudeSq(*q);

	if(mag > 1.00001 || mag < .99999)
	{
		mag = sqrt(mag);
		scale(q, 1/mag);
	}
}


//***********************
//*******************************
//Scaling
//*******************************
//***********************
void scale(Mat4* m, float s)
{
	(*m).x[0] *= s;
	(*m).x[1] *= s;
	(*m).x[2] *= s;
	(*m).x[3] *= s;

	(*m).y[0] *= s;
	(*m).y[1] *= s;
	(*m).y[2] *= s;
	(*m).y[3] *= s;

	(*m).z[0] *= s;
	(*m).z[1] *= s;
	(*m).z[2] *= s;
	(*m).z[3] *= s;

	(*m).w[0] *= s;
	(*m).w[1] *= s;
	(*m).w[2] *= s;
	(*m).w[3] *= s;
}

XMFLOAT3 scale(XMFLOAT3 v, float s)
{
	return XMFLOAT3(v.x*s, v.y*s, v.z*s);
}

void scale(Quaternion* q, float s)
{
	(*q).w *= s;
	(*q).x *= s;
	(*q).y *= s;
	(*q).z *= s;
}

Quaternion scale(Quaternion q, float s)
{
	(q).w *= s;
	(q).x *= s;
	(q).y *= s;
	(q).z *= s;

	return q;
}


//***********************
//*******************************
//Interpolations
//*******************************
//***********************

//SLERP CODE
//"3D Math Primer for Graphics and Game Development"
//Chapter 10: Page 176-177
Quaternion slerp(Quaternion q1, Quaternion q2, float t)
{
	float cosA = dotProduct(q1, q2);
	float c1 = 0;
	float c2 = 0;

	if( cosA < 0.0 )
	{
		scale(q2, -1);
		cosA *= -1;
	}

	if( cosA > .999 )
	{
		nLerp(q1, q2, t);
	}
	else
	{
		float sinA = sqrt( 1.0 - pow(cosA, 2) );

		float angle = atan2(sinA, cosA);

		float recSinA = 1/sinA;

		c1 = sin((1.0-t)*angle)*recSinA;
		c2 = sin(t*angle)*recSinA;
	}

	scale(&q1, c1);
	scale(&q2, c2);

	Quaternion q(q1.w+q2.w, q1.x+q2.x, q1.y+q2.y, q1.z+q2.z);

	return q;
}
Quaternion nLerp(Quaternion q1, Quaternion q2, float t)
{
	float dot = dotProduct(q1, q2);

	scale(&q1, 1-t);
	scale(&q2, t);

	Quaternion q(q1.w+q2.w, q1.x+q2.x, q1.y+q2.y, q1.z+q2.z);
	normalize(&q);

	return q;
}

Quaternion conjugate(Quaternion q)
{
	return Quaternion(q.w, -q.x, -q.y, -q.z);
}

XMFLOAT3 transformVector(Quaternion q, XMFLOAT3 v)
{
	Quaternion quatConj = conjugate(q);
	Quaternion vec(0.0, v.x, v.y, v.z);

	vec = mult(q, vec);
	vec = mult(vec, quatConj);

	return XMFLOAT3( vec.x, vec.y, vec.z );
}

Quaternion toQuatFromXMFloat3( XMFLOAT3 v )
{
	return Quaternion( 0.0, v.x, v.y, v.z );
}