#pragma once
#include "afxwin.h"

class CVector3D
{
public:
	CVector3D() : x(0.0f), y(0.0f), z(0.0f){}
	~CVector3D(){};

	float x;
	float y;
	float z;

	void trace(const char string[]);

	bool operator==(const CVector3D &v);
	inline bool operator!=(const CVector3D &v){return !operator==(v);};
	//Vector3D & operator = (const Vector3D &v);
	CVector3D operator + (const CVector3D &v);
	CVector3D operator - (const CVector3D &v);
	// scalar Division
	CVector3D operator / (float scalar);
	// scalar multiplication
	CVector3D operator * (float scalar);
	// dot product
	float operator * (CVector3D &v);
	float CrossProduct(const CVector3D & v);

	float facing(CVector3D rayCast[]);
	bool hitTest(CVector3D rayCast[], float radius);
	CVector3D operator^(float power);
};