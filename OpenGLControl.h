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

	void	oglCreate(CRect rect, CWnd *parent);

private:
	CWnd	*hWnd;
	HDC		hdc;
	HGLRC	hrc;
	int		m_nPixelFormat;
	CRect	m_rect;
	CRect	m_oldWindow;
	CRect	m_originalRect;

	void    oglInitialize(void);

	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDraw(CDC *pDC);
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
};

