#pragma once
#include "afxwin.h"
#include <vector>

#include "iColorRGBA.h"
#include "3dVector.h"

#include <gl\GL.h>
#include <gl\GLU.h>

#define Points_Add		0
#define Points_Remove	1

class C3DLine
{
public:
	C3DLine();
	virtual ~C3DLine(void){};
	
	float m_fPointSize;
	float m_fLineSize;
	int   m_iCurrentSel; // id for our currently selected object
	int   m_iAddRem;	 // are we adding points or removing points

	iColorRGBA	m_baseCol;
	iColorRGBA  m_selCol;

	std::vector<CVector3D>	m_Line;
	std::vector<iColorRGBA> m_LineCol;

	void CreateLine();
	void OpenGLDraw();
	bool HitTest(CVector3D rayCast[], float radius);
	
	void addPoint(CVector3D point);
	void movePoint(CVector3D moveto);
	void removePoint();

	void orderPoints();
};