#pragma once
#include "afxwin.h"
#include <gl\GL.h>
#include <gl\GLU.h>

class CLineEditControl : public CWnd
{
public:
	CLineEditControl(void);
	virtual ~CLineEditControl(void);

	UINT_PTR m_unpTimer;  // Timer
	CWnd	*hWnd;
	HDC		hdc;
	HGLRC	hrc;
	int		m_nPixelFormat;
	CRect	m_rect;
	CRect   m_oldWindow;
	CRect	m_originalRect;

	BOOL m_bIsMaximized;

	float	m_fLastX;		// last known mouse X position
	float   m_fLastY;		// last known mouse Y position
	
	float	m_fPosX;		// X position of the model in camera View
	float	m_fPosY;		// Y position of the model in camera View
	float	m_fZoom;		// Zoom on model in camera View

	void	oglInitialize(void);
	void	oglDrawScene(void);
	void	oglCreate(CRect rect, CWnd *parent);

	afx_msg int		OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void	OnSize(UINT nType, int cx, int cy);
	afx_msg void	OnTimer(UINT_PTR nIDEvent);
	afx_msg void	OnDraw(CDC *pDC);
	afx_msg void	OnPaint();
	afx_msg void	OnMouseMove(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP();
};
