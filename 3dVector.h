#pragma once
#include "afxwin.h"

class Vector3D
{
public:
	Vector3D() : x(0.0f), y(0.0f), z(0.0f){}
	~Vector3D(){};

	float x;
	float y;
	float z;

	bool operator==(const Vector3D &v);
	inline bool operator!=(const Vector3D &v){return !operator==(v);};
	//Vector3D & operator = (const Vector3D &v);
	Vector3D operator + (const Vector3D &v);
	Vector3D operator - (const Vector3D &v);
	// scalar multiplication
	Vector3D operator * (float scalar);
	// dot product
	float operator * (Vector3D &v);
	float CrossProduct(const Vector3D & v);

	float facing(Vector3D rayCast[]);
	bool hitTest(Vector3D rayCast[], float radius);
	Vector3D operator^(float power);
};