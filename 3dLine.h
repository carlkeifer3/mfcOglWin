#pragma once
#include "afxwin.h"
#include <vector>

#include "iColorRGBA.h"
#include "3dVector.h"

#include <gl\GL.h>
#include <gl\GLU.h>

class C3DLine
{
public:
	C3DLine();
	virtual ~C3DLine(void){};
	
	float m_fPointSize;
	float m_fLineSize;
	int   m_iCurrentSel; // id for our currently selected object

	iColorRGBA	m_baseCol;
	iColorRGBA  m_selCol;

	std::vector<Vector3D>	m_Line;
	std::vector<iColorRGBA> m_LineCol;

	void CreateLine();
	void OpenGLDraw();
	bool HitTest(Vector3D rayCast[], float radius);
	
	void addPoint(Vector3D point);
	void movePoint(Vector3D moveto);
};