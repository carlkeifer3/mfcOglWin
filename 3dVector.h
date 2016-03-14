#pragma once
#include "afxwin.h"

class Vector3D
{
public:
	Vector3D() : x(0.0f), y(0.0f), z(0.0f){}
	~Vector3D();

	float x;
	float y;
	float z;

	bool operator == (const Vector3D &v1, const Vector3D &v2);
	bool operator != (const Vector3D &v1, const Vector3D &v2);
	Vector3D & operator = (const Vector3D &v);
	Vector3D operator + (const Vector3D &v1, const Vector3D &v2);
	Vector3D operator - (const Vector3D &v1, const Vector3D &v2);
	// scalar multiplication
	Vector3D operator *  (const Vector3D &v, float scalar);
	Vector3D operator *  (float scalar, const Vector3D &v);
	// dot product
	friend float operator * (Vector3D &v1, Vector3D &v2);


	friend float CrossProduct(const Vector3D & v1, const Vector3D &v2);


};