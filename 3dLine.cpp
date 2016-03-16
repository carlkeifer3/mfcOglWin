//******************************************************** 
//**
//**	3DLine.cpp - library for generating useful line objects
//**
//**	Author - Carl Keifer
//**
//*********************************************************

#include "stdafx.h"
#include "3dLine.h"
#include <algorithm>

C3DLine::C3DLine()
{
	m_drawLine = TRUE;
	m_drawPoints = TRUE;

	m_PointCol.r = 000;
	m_PointCol.g = 000;
	m_PointCol.b = 000;
	m_PointCol.a = 255;
	
	m_LineCol.r = 000;
	m_LineCol.g = 155;
	m_LineCol.b = 255;
	m_LineCol.a = 255;

	m_selCol.a = 000;
	m_selCol.g = 255;
	m_selCol.b = 150;
	m_selCol.a = 255;

	m_fPointSize = 10.0f;

	m_iAddRem = Points_Add;
	m_iCurrentSel = NULL;
}

int C3DLine::addPoint(CVector3D point)
{
	// here we should check point to see if it exists
	int v = vertCheck(point);

	// new vertex
	if ( v == NULL)
	{
		m_vertices.push_back(point);
		m_VertCol.push_back(m_PointCol);

		orderPoints();

		for( int i=0; i<(int)m_vertices.size(); i++)
		{
			if(m_vertices[i] == point)
			{
				m_iCurrentSel = i;
				return i;
			}
		}
	}
	else
	{
		m_iCurrentSel = v;
		return v;
	}
	return NULL;
}

int C3DLine::vertCheck(CVector3D v)
{
	bool vCheck = FALSE;
	int i;

	// iterate the list of verts
	// compare the current vert with the supplied vert
	for(i=0; i< (int)m_vertices.size(); i++)
	{
		if(v == m_vertices[i])
		{
			return i;
		}
	}

	return NULL;
}

void C3DLine::setSegment(CVector3D vertA, CVector3D vertB)
{
	CLineIndex segment;

	segment.a = addPoint(vertA);
	segment.b = addPoint(vertB);

	// there should be a check to see if this already exists
	// but for now this is fine

	m_Segments.push_back(segment);
}

void C3DLine::removePoint()
{
	m_vertices.erase(m_vertices.begin() + m_iCurrentSel);
	orderPoints();
}

void C3DLine::orderPoints()
{
	// this method does not work for everything
	// only single lines that are created by the line editor

	auto comparison = [](CVector3D left, CVector3D right)->bool{
		return(left.y > right.y);
	};

	std::sort(m_vertices.begin(), m_vertices.end(), comparison);
	
	m_Segments.clear();
	m_segmentCol.clear();

	int j = 0;

	// now that the list is ordered by axis set up our segments
	for ( int i=1; i< (int)m_vertices.size(); i++)
	{
		CLineIndex segment;

		segment.a = j;
		segment.b = i;
		m_Segments.push_back(segment);
		m_segmentCol.push_back(m_LineCol);
		j=i;
	}
}

void C3DLine::movePoint(CVector3D moveto)
{
	m_vertices[m_iCurrentSel].x = moveto.x;
	m_vertices[m_iCurrentSel].y = moveto.y;
	m_vertices[m_iCurrentSel].z = moveto.z;
}

void C3DLine::CreateLine()
{
	CVector3D point;
	CLineIndex segment;

	point.x = 150.0f;
	point.y = 420.0f;
	point.z = 0.0f;

	m_vertices.push_back(point);
	m_VertCol.push_back(m_PointCol);

	point.x = 150.0f;
	point.y = 15.0f;
	point.z = 0.0f;

	m_vertices.push_back(point);
	m_VertCol.push_back(m_PointCol);

	segment.a = 0;
	segment.b = 1;

	m_Segments.push_back(segment);
	m_segmentCol.push_back(m_LineCol);
}

void C3DLine::ClearLine()
{
	m_vertices.clear();
	m_Segments.clear();
	m_VertCol.clear();
	m_segmentCol.clear();
}

void C3DLine::OpenGLDraw()
{
	if ( m_drawLine == TRUE )
	{
		drawLine();
	}
	
	if ( m_drawPoints = TRUE )
	{
		drawPoints();
	}
}

void C3DLine::drawLine()
{
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_FRONT, GL_FILL);

	glLineWidth(2.0f);
	glBegin(GL_LINES);
	for(int i=0; i<(int)m_Segments.size(); i++)
	{
		glColor4ub( m_segmentCol[i].r, m_segmentCol[i].g, m_segmentCol[i].b, m_segmentCol[i].a);
		glVertex3f( m_vertices[m_Segments[i].a].x, m_vertices[m_Segments[i].a].y, m_vertices[m_Segments[i].a].z);
		glVertex3f( m_vertices[m_Segments[i].b].x, m_vertices[m_Segments[i].b].y, m_vertices[m_Segments[i].b].z);
	}
	glEnd();
}

void C3DLine::drawPoints()
{
	glPointSize(m_fPointSize);
	glBegin(GL_POINTS);
	for(int i=0; i<(int)m_vertices.size(); i++)
	{
		glColor4ub( m_VertCol[i].r, m_VertCol[i].g, m_VertCol[i].b, m_VertCol[i].a);
		glVertex3f( m_vertices[i].x, m_vertices[i].y, m_vertices[i].z);
	}
	glEnd();
}

bool C3DLine::HitTest(CVector3D rayCast[], float radius)
{
	//these should be separate functions

	// now we can run our hit test on our vertices
	for(int i=0; i<(int)m_vertices.size();i++)
	{
		bool hit = m_vertices[i].hitTest(rayCast, m_fPointSize);

		if (hit == TRUE)
		{
			m_VertCol[i] = m_VertCol[i].set(m_selCol);

			m_iCurrentSel = i;

			return TRUE;
		}
		else
		{
			m_VertCol[i] = m_VertCol[i].set(m_PointCol);

			m_iCurrentSel = NULL;
		}
	}

	// now we can run our hit test on our segments


	return FALSE;
}