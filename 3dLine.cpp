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
	m_selCol.b = 000;
	m_selCol.a = 255;

	m_fPointSize = 10.0f;
	m_fLineSize = 2.0f;

	m_iAddRem = Points_Add;
	m_iVertID = NULL;
}

int C3DLine::addPoint(CVector3D point)
{
	if(m_iSegID !=  m_iMaxSegs)
	{
		// here we should check point to see if it exists
		int v = vertCheck(point);

		// new vertex
		if ( v == NULL)
		{
			m_vertices.push_back(point);
			m_VertCol.push_back(m_PointCol);
			m_iMaxVerts = m_vertices.size()+2;

			int V = m_vertices.size()-1;

			//orderPoints();
			int b = m_Segments[m_iSegID].b;
			// now we link the new point to our selected segment
			m_Segments[m_iSegID].b = V;

			// then we make a new segment to go the rest of the way
			CLineIndex segment;
			segment.a = V;
			segment.b = b;

			m_Segments.push_back(segment);
			m_segmentCol.push_back(m_LineCol);
			m_iMaxSegs = m_Segments.size()+2;

			m_iVertID = V;
			m_iSegID = m_iMaxSegs;
			return V;
		}
		else
		{
			m_iVertID = v;
			return v;
		}
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

	m_fLineLength = LineLength();
}

float C3DLine::LineLength()
{
	float length = 0.0f;

	for ( int i=0; i<(int)m_Segments.size(); i++)
	{
		float segLen =  segmentLength(m_vertices[m_Segments[i].a], m_vertices[m_Segments[i].b]);
		length += length + segLen;
	}

	return length;
}

float C3DLine::segmentLength(CVector3D vertA, CVector3D vertB)
{
	CVector3D D = vertA - vertB;
	D = D^2.0f;

	return sqrt((float)(D.x + D.y + D.z));
}

CVector3D C3DLine::ClosestPoint(CVector3D point, int seg)
{
	int p = m_Segments[seg].a;
	int v = m_Segments[seg].b;

	CVector3D lineDiffVect = m_vertices[v] - m_vertices[p];

	CVector3D w = point - m_vertices[p];
	float vsq = lineDiffVect * lineDiffVect;
	float proj = w * lineDiffVect;

	return m_vertices[p] + lineDiffVect*(proj/vsq);
}

void C3DLine::removePoint()
{
	// find the currently grabbed point in the array

	// then find out which segments he belongs to

	// now we should remove the one segment

	// and re assign the other

	// now we delete the vertice from the array
	m_vertices.erase(m_vertices.begin() + m_iVertID);

	// this should no longer be neccessary
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
	m_vertices[m_iVertID].x = moveto.x;
	m_vertices[m_iVertID].y = moveto.y;
	m_vertices[m_iVertID].z = moveto.z;
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
	m_iMaxVerts = m_vertices.size()+2;

	segment.a = 0;
	segment.b = 1;

	m_Segments.push_back(segment);
	m_segmentCol.push_back(m_LineCol);
	m_iMaxSegs = m_Segments.size()+2;
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

	glLineWidth(m_fLineSize);
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

			m_iVertID = i;

			return TRUE;
		}
		else
		{
			m_VertCol[i] = m_VertCol[i].set(m_PointCol);

			m_iVertID = m_iMaxVerts;
		}
	}

	rayCast[0].z = 0.0f;

	// now we can run our hit test on our segments
	for (int i=0; i<(int)m_Segments.size();i++)
	{


		CVector3D check = ClosestPoint(rayCast[0], i);
		float distance = segmentLength(rayCast[0], check);

		if (distance < 4.0f)
		{
			if (m_iVertID == m_iMaxVerts)
			{
				m_segmentCol[i] = m_segmentCol[i].set(m_selCol);
				m_iSegID = i;
				break;
			}
		}
		else
		{
			m_segmentCol[i] = m_segmentCol[i].set(m_LineCol);
			m_iSegID = m_iMaxSegs;
		}
	}

	return FALSE;
}
