#include "stdafx.h"
#include "3dVector.h"

#include <math.h>

void CVector3D::trace(const char string[])
{
	CVector3D vector = *this;
	
	TRACE("\n*****************************************\n");
	TRACE("**	%s\n", string);
	TRACE("**		X: %i \n", vector.x);
	TRACE("**		Y: %i \n", vector.y);
	TRACE("**		Z: %i \n", vector.z);
	TRACE("*****************************************\n");
}

bool CVector3D::operator==(const CVector3D &v)
{
	CVector3D vector = *this;

	if( vector.x == v.x && vector.y == v.y && vector.z == v.z)
	{
		return TRUE;
	}

	return FALSE;
}

CVector3D CVector3D::operator+(const CVector3D &v)
{
	CVector3D vector = *this;

	vector.x = vector.x + v.x;
	vector.y = vector.y + v.y;
	vector.z = vector.z + v.z;

	return vector;
}

CVector3D CVector3D::operator-(const CVector3D &v)
{
	CVector3D vector = *this;

	vector.x = vector.x - v.x;
	vector.y = vector.y - v.y;
	vector.z = vector.z - v.z;

	return vector;
}

CVector3D CVector3D::operator / (float scalar)
{
	CVector3D vector = *this;

	vector.x = vector.x / scalar;
	vector.y = vector.y / scalar;
	vector.z = vector.z / scalar;

	return vector;

}

CVector3D CVector3D::operator * (float scalar)
{
	CVector3D vector = *this;

	vector.x = vector.x * scalar;
	vector.y = vector.y * scalar;
	vector.z = vector.z * scalar;

	return vector;
}

float CVector3D::operator * (CVector3D &v)
{
	CVector3D vector = *this;
	float product;

	product  = vector.x * v.x;
	product += vector.y * v.y;
	product += vector.z * v.z;

	return product;
}

float CVector3D::CrossProduct(const CVector3D & v)
{
	CVector3D vector = *this;

	// space to create a cross product check

	return 0.0;
}

float CVector3D::facing(CVector3D rayCast[])
{
	CVector3D vector = *this;

	// this is the vector from the origin to the hit test center
	vector = vector - rayCast[0];

	float tc = vector * rayCast[2];

	return tc;
}

bool CVector3D::hitTest(CVector3D rayCast[], float radius)
{
	CVector3D vector = *this;

	float tc = vector.facing(rayCast);

	if (tc < 0)
	{
		// the intersection isn't even pointing in the right direction
		return FALSE;
	}
	
	// l is the distance from the center to the origin
	vector = vector - rayCast[0];
	vector = vector^2.0f;
	float l = sqrt(vector.x + vector.y + vector.z);

	// now we use the pythagorean theorem to determine if
	// our vector passes the hit test
	float la = tc * tc;
	float lb = l * l;

	float D = sqrt(abs(la- lb)); // the lenth of segment c-t

	// Now if the calculations are correct and the ray is passing the sphere.
	// t-e-a will be less than or equal to our radius
	if (D <= radius)
	{
		// The check has passed.
		// our ray is touching this point
		return TRUE;
	}
	else
	{
		// the check has failed it is too far from the center point
		return FALSE;
	}
}

CVector3D CVector3D::operator^(float power)
{
	CVector3D vector = *this;

	vector.x = pow(vector.x, power);
	vector.y = pow(vector.y, power);
	vector.z = pow(vector.z, power);

	return vector;
}


