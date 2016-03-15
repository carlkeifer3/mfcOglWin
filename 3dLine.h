#pragma once
#include "afxwin.h"
#include <vector>

#include "iColorRGBA.h"
#include "3dVector.h"

class C3DLine
{
public:
	C3DLine();
	virtual ~C3DLine();
	
	iColorRGBA	baseCol;
	iColorRGBA  selCol;

	std::vector<Vector3D>	line;
	std::vector<iColorRGBA> lineCol;

	void CreateLine();
};