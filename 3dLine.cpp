#include "stdafx.h"
#include "3dLine.h"

C3DLine::C3DLine()
{
	baseCol.r = 000;
	baseCol.g = 000;
	baseCol.b = 000;
	baseCol.a = 255;
	
	selCol.a = 000;
	selCol.g = 255;
	selCol.b = 150;
	selCol.a = 255;
}

void C3DLine::CreateLine()
{
	Vector3D point;
	iColorRGBA color;

	color.set(baseCol);

	point.x = 150.0f;
	point.y = 300.0f;
	point.z = 0.0f;

	line.push_back(point);
	lineCol.push_back(color);

	point.x = 150.0f;
	point.y = 20.0f;
	point.z = 0.0f;

	line.push_back(point);
	lineCol.push_back(color);
}
