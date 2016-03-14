#pragma once
#include "afxwin.h"
#include <gl\GL.h>
#include <gl\GLU.h>

class COpenGLControl : public CWnd
{
public:
	COpenGLControl(void);
	virtual ~COpenGLControl(void);

	UINT_PTR m_unpTimer;  // Timer

private:
	CWnd	*hWnd;
	HDC		hdc;
	HGLRC	hrc;
	int		m_nPixelFormat;
	CRect	m_rect;
	CRect	m_oldWindow;
	CRect	m_originalRect;

	void	oglCreate(CRect rect, CWnd *parent);

	
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
};

