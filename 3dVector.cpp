#include "stdafx.h"
#include "3dVector.h"

#include <math.h>


void Vector3D::trace(const char string[])
{
	Vector3D vector = *this;
	
	TRACE("\n*****************************************\n");
	TRACE("**	%s\n", string);
	TRACE("**		X: %i \n", vector.x);
	TRACE("**		Y: %i \n", vector.y);
	TRACE("**		Z: %i \n", vector.z);
	TRACE("*****************************************\n");
}

bool Vector3D::operator==(const Vector3D &v)
{
	Vector3D vector = *this;

	if( vector.x == v.x && vector.y == v.x && vector.z == v.z)
	{
		return TRUE;
	}

	return FALSE;
}

Vector3D Vector3D::operator+(const Vector3D &v)
{
	Vector3D vector = *this;

	vector.x = vector.x + v.x;
	vector.y = vector.y + v.y;
	vector.z = vector.z + v.z;

	return vector;
}

Vector3D Vector3D::operator-(const Vector3D &v)
{
	Vector3D vector = *this;

	vector.x = vector.x - v.x;
	vector.y = vector.y - v.y;
	vector.z = vector.z - v.z;

	return vector;
}

Vector3D Vector3D::operator / (float scalar)
{
	Vector3D vector = *this;

	vector.x = vector.x / scalar;
	vector.y = vector.y / scalar;
	vector.z = vector.z / scalar;

	return vector;

}

Vector3D Vector3D::operator * (float scalar)
{
	Vector3D vector = *this;

	vector.x = vector.x * scalar;
	vector.y = vector.y * scalar;
	vector.z = vector.z * scalar;

	return vector;
}

float Vector3D::operator * (Vector3D &v)
{
	Vector3D vector = *this;
	float product;

	product  = vector.x * v.x;
	product += vector.y * v.y;
	product += vector.z * v.z;

	return product;
}

float Vector3D::CrossProduct(const Vector3D & v)
{
	Vector3D vector = *this;

	// space to create a cross product check

	return 0.0;
}

float Vector3D::facing(Vector3D rayCast[])
{
	Vector3D vector = *this;

	// this is the vector from the origin to the hit test center
	vector = vector - rayCast[0];

	float tc = vector * rayCast[2];

	return tc;
}

bool Vector3D::hitTest(Vector3D rayCast[], float radius)
{
	Vector3D vector = *this;

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

Vector3D Vector3D::operator^(float power)
{
	Vector3D vector = *this;

	vector.x = pow(vector.x, power);
	vector.y = pow(vector.y, power);
	vector.z = pow(vector.z, power);

	return vector;
}


