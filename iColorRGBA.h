#pragma once
#include "afxwin.h"

class iColorRGBA
{
	int r;
	int g;
	int b;
	int a;

	void set(iColorRGBA color)
	{
		iColorRGBA baseCol = *this;

		baseCol.r = color.r;
		baseCol.g = color.g;
		baseCol.b = color.b;
		baseCol.a = color.a;
	}

};