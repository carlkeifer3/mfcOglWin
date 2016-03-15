#pragma once
#include "afxwin.h"

class iColorRGBA
{
public:
	int r;
	int g;
	int b;
	int a;

	iColorRGBA set(iColorRGBA color)
	{
		iColorRGBA baseCol = *this;

		baseCol.r = color.r;
		baseCol.g = color.g;
		baseCol.b = color.b;
		baseCol.a = color.a;

		return baseCol;
	}

};