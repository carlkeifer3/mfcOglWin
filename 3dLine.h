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
	
	iColorRGBA	baseCol;
	iColorRGBA  selCol;

	std::vector<Vector3D>	line;
	std::vector<iColorRGBA> lineCol;

	void CreateLine();
	void OpenGLDraw();
	void HitTest(Vector3D rayCast[], float radius);
};