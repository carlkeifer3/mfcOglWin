#include "stdafx.h"
#include "3dLine.h"

#include <algorithm>

C3DLine::C3DLine()
{
	m_baseCol.r = 000;
	m_baseCol.g = 000;
	m_baseCol.b = 000;
	m_baseCol.a = 255;
	
	m_selCol.a = 000;
	m_selCol.g = 255;
	m_selCol.b = 150;
	m_selCol.a = 255;

	m_fPointSize = 10.0f;

	m_iAddRem = Points_Add;
}

void C3DLine::addPoint(Vector3D point)
{
	iColorRGBA color;
	color.set(m_baseCol);
	
	m_Line.push_back(point);
	m_LineCol.push_back(color);

	orderPoints();

	for( int i=0; i<(int)m_Line.size(); i++)
	{
		if(m_Line[i] == point)
		{
			m_iCurrentSel = i;
			break;
		}
	}
}

void C3DLine::removePoint()
{
	m_Line.erase(m_Line.begin() + m_iCurrentSel);
	orderPoints();
}

void C3DLine::orderPoints()
{
	auto comparison = [](Vector3D left, Vector3D right)->bool{
		return(left.y > right.y);
	};

	std::sort(m_Line.begin(), m_Line.end(), comparison);
}

void C3DLine::movePoint(Vector3D moveto)
{
	m_Line[m_iCurrentSel].x = moveto.x;
	m_Line[m_iCurrentSel].y = moveto.y;
	m_Line[m_iCurrentSel].z = moveto.z;
}

void C3DLine::CreateLine()
{
	Vector3D point;
	iColorRGBA color;

	color.set(m_baseCol);

	point.x = 150.0f;
	point.y = 420.0f;
	point.z = 0.0f;

	m_Line.push_back(point);
	m_LineCol.push_back(color);

	point.x = 150.0f;
	point.y = 15.0f;
	point.z = 0.0f;

	m_Line.push_back(point);
	m_LineCol.push_back(color);
}

void C3DLine::OpenGLDraw()
{
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_FRONT, GL_FILL);

	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glColor4ub( 000, 155, 255, 255);
	for(int i=0; i<(int)m_Line.size()-1; i++)
	{
		glVertex3f( m_Line[i].x, m_Line[i].y, m_Line[i].z);
		glVertex3f( m_Line[i+1].x, m_Line[i+1].y, m_Line[i+1].z);
	}
	glEnd();

	glPointSize(m_fPointSize);
	glBegin(GL_POINTS);
	for(int i=0; i<(int)m_Line.size(); i++)
	{
		glColor4ub( m_LineCol[i].r, m_LineCol[i].g, m_LineCol[i].b, m_LineCol[i].a);
		glVertex3f( m_Line[i].x, m_Line[i].y, m_Line[i].z);
	}
	glEnd();
}

bool C3DLine::HitTest(Vector3D rayCast[], float radius)
{
	// now we can run our hit test
	for(int i=0; i<(int)m_Line.size();i++)
	{
		bool hit = m_Line[i].hitTest(rayCast, m_fPointSize);

		if (hit == TRUE)
		{
			m_LineCol[i] = m_LineCol[i].set(m_selCol);

			m_iCurrentSel = i;

			return TRUE;
		}
		else
		{
			m_LineCol[i] = m_LineCol[i].set(m_baseCol);

			m_iCurrentSel = m_LineCol.size() + 2;
		}
	}
	return FALSE;
}