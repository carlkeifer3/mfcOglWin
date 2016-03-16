#ifndef __3DLINE_H__
#define __3DLINE_H__

#pragma once
#include "afxwin.h"
#include <vector>

#include "iColorRGBA.h"
#include "3dVector.h"

#include <gl\GL.h>
#include <gl\GLU.h>

#define Points_Add		0
#define Points_Remove	1

typedef struct CLineIndex
{
	int a;
	int b;
}CLineIndex;

class C3DLine
{
public:
	C3DLine();
	virtual ~C3DLine(void){};
	
	float m_fPointSize;
	float m_fLineSize;
	float m_fLineLength;	// float variable that stores our line length
	int   m_iVertID;		// id for our currently selected vertex
	int   m_iSegID;			// id for our currently selected segment
	int   m_iAddRem;		// are we adding points or removing points

	bool m_drawLine;
	bool m_drawPoints;

	iColorRGBA	m_PointCol;
	iColorRGBA  m_LineCol;
	iColorRGBA  m_selCol;

	void CreateLine();
	void ClearLine();

	void OpenGLDraw();
	bool HitTest(CVector3D rayCast[], float radius);
	
	float LineLength();
	float segmentLength(CVector3D vertA, CVector3D vertB);
	CVector3D ClosestPoint(CVector3D point, int seg);

	int addPoint(CVector3D point);
	void movePoint(CVector3D moveto);
	void removePoint();
	
	void setSegment(CVector3D vertA, CVector3D vertB);

private:

	std::vector<CVector3D>	m_vertices;		// dynamic array that holds all of our points
	std::vector<CLineIndex>	m_Segments;		// dynamic index array that lists all line segments
	std::vector<iColorRGBA> m_VertCol;		// dynamic index of all vertex colors
	std::vector<iColorRGBA> m_segmentCol;	// dynamic index of all segment colors

	int vertCheck(CVector3D v);

	void drawLine();
	void drawPoints();
	void orderPoints();
};

#endif // __3DLINE_H__