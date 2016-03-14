
// oglLineEdit.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CoglLineEditApp:
// See oglLineEdit.cpp for the implementation of this class
//

class CoglLineEditApp : public CWinApp
{
public:
	CoglLineEditApp();

// Overrides
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CoglLineEditApp theApp;