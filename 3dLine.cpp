#include "stdafx.h"
#include "3dLine.h"

#include <algorithm>

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

	pointSize = 15.0f;
}

void C3DLine::addPoint(Vector3D point)
{
	iColorRGBA color;
	color.set(baseCol);
	
	line.push_back(point);
	lineCol.push_back(color);

	auto comparison = [](Vector3D left, Vector3D right)->bool{
		return(left.y > right.y);
	};

	std::sort(line.begin(), line.end(), comparison);
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

void C3DLine::OpenGLDraw()
{
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_FRONT, GL_FILL);

	glLineWidth(2.0f);
	glBegin(GL_LINE_LOOP);
	glColor4ub( 000, 155, 255, 255);
	for(int i=0; i<(int)line.size(); i++)
	{
		glVertex3f( line[i].x, line[i].y, line[i].z);
	}
	glEnd();

	glPointSize(pointSize);
	glBegin(GL_POINTS);
	for(int i=0; i<(int)line.size(); i++)
	{
		glColor4ub( lineCol[i].r, lineCol[i].g, lineCol[i].b, lineCol[i].a);
		glVertex3f( line[i].x, line[i].y, line[i].z);
	}
	glEnd();
}

bool C3DLine::HitTest(Vector3D rayCast[], float radius)
{
	// now we can run our hit test
	for(int i=0; i<(int)line.size();i++)
	{
		bool hit = line[i].hitTest(rayCast, pointSize);

		if (hit == TRUE)
		{
			lineCol[i] = lineCol[i].set(selCol);
			return TRUE;
		}
		else
		{
			lineCol[i] = lineCol[i].set(baseCol);
		}
	}
	return FALSE;
}