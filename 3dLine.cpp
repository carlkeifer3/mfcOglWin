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

void C3DLine::OpenGLDraw()
{
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_FRONT, GL_FILL);

	glLineWidth(2.0f);
	glBegin(GL_LINES);
	for(int i=0; i<(int)line.size(); i++)
	{
		glColor4ub( 000, 155, 255, 255);
		glVertex3f( line[i].x, line[i].y, line[i].z);
	}
	glEnd();
	glPointSize(15.0f);
	glBegin(GL_POINTS);
	for(int i=0; i<(int)line.size(); i++)
	{
		glColor4ub( lineCol[i].r, lineCol[i].g, lineCol[i].b, lineCol[i].a);
		glVertex3f( line[i].x, line[i].y, line[i].z);
	}
	glEnd();
}

void C3DLine::HitTest(Vector3D rayCast[], float radius)
{
	// now we can run our hit test
	for(int i=0; i<(int)line.size();i++)
	{
		bool hit = line[i].hitTest(rayCast, 15.0f);

		if (hit == TRUE)
		{
			lineCol[i] = lineCol[i].set(selCol);
		}
		else
		{
			lineCol[i] = lineCol[i].set(baseCol);
		}
	}
}