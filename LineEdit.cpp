#include "stdafx.h"
#include "LineEdit.h"

BEGIN_MESSAGE_MAP(CLineEditControl, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

CLineEditControl::CLineEditControl(void)
{
	m_fPosX  = 0.0f;
	m_fPosY  = 0.0f;
	m_fZoom  = 0.0f;
	m_fZoom  = 5.0f;
}

CLineEditControl::~CLineEditControl(void)
{

}

void CLineEditControl::oglCreate(CRect rect, CWnd *parent)
{
	CString className = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_OWNDC, NULL,
		(HBRUSH)GetStockObject(BLACK_BRUSH), NULL);

	CreateEx(0, className, _T("OpenGL"), WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, rect, parent, 0);

	// Set initial variables values
	m_oldWindow		= rect;
	m_originalRect  = rect;

	hWnd = parent;
}

int CLineEditControl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == 1)
		return -1;

	oglInitialize();

	return 0;
}

void CLineEditControl::oglInitialize(void)
{
	// Initial Setup
	//
	static PIXELFORMATDESCRIPTOR pfd = 
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,			// bit depth
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		16,			// z-buffer depth
		0, 0, 0, 0, 0, 0, 0
	};

	// Get device context only once.
	hdc = GetDC()->m_hDC;

	// Pixel format.
	m_nPixelFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, m_nPixelFormat, &pfd);

	// Create the OpenGL Rendering Context.
	hrc = wglCreateContext(hdc);
	wglMakeCurrent(hdc, hrc);

	//basic Setup:
	//
	// Set color to use when clearing the background
	glClearColor(0.5f, 0.5f, 0.55f, 1.0f);
	glClearDepth(1.0f);

	//glFrontFace(GL_CW);		// sets winding order to clockwise
	//glCullFace(GL_BACK);	// removes all the back faces

	CreateLine();

	// Send draw request
	OnDraw(NULL);
}

void CLineEditControl::OnPaint()
{
	// CPaintDC dc(this);
	ValidateRect(NULL);
}

void CLineEditControl::OnDraw(CDC *pDC)
{
	 glLoadIdentity();
	 glTranslatef(0.0f, 0.0f, -m_fZoom);
	 glTranslatef(m_fPosX, m_fPosY, 0.0f);
}

void CLineEditControl::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case 1:
		{
			// Clear color and depth buffer bits
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//Draw OpenGL Scene
			oglDrawScene();

			// swap buffers
			SwapBuffers(hdc);

			break;
		}
	default:
		break;
	}

	CWnd::OnTimer(nIDEvent);
}

void CLineEditControl::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	if ( 0 >= cx || 0 >= cy || nType == SIZE_MINIMIZED)
		return;

	// Map the OpenGL coordinates
	glViewport(0, 0, cx, cy);

	//projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
			
	// set up an orthographic projection with the same near clip plane
	glOrtho(0, cx, 0, cy, -1000, 1000);

	// Model Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void CLineEditControl::CreateLine()
{
	//create line object
	line.CreateLine();
}

void CLineEditControl::oglDrawScene(void)
{
	// draw line object
	line.OpenGLDraw();
}

void CLineEditControl::OnMouseMove(UINT nFlags, CPoint point)
{
	int diffX = (int)(point.x - m_fLastX);
	int diffY = (int)(point.y - m_fLastY);
	m_fLastX  = (float)point.x;
	m_fLastY  = (float)point.y;

	//check our line object for hits
	GLint viewport[4];
	glGetIntegerv (GL_VIEWPORT, viewport);
	
	float realy = (float)viewport[3] - (GLint) point.y - 1;
	CVector3D rayCast[3];

	rayCast[0].x = (float)point.x;
	rayCast[0].y = realy;
	rayCast[0].z = -100.0f;

	rayCast[1].x = (float)point.x;
	rayCast[1].y = realy;
	rayCast[1].z = 100.0f;

	// Left Mouse Button
	if (nFlags & MK_LBUTTON)
	{	
		if(line.m_iAddRem == Points_Add && line.m_iVertID != NULL)
		{
			// there should be a currently active selection

			CVector3D vector;
			vector.x = rayCast[0].x;
			vector.y = rayCast[0].y;
			vector.z = 0.0f;

			line.movePoint(vector);
		}

	}
	// Middle Mouse Button
	//else if ( nFlags & MK_MBUTTON)
	//{
	//	m_fZoom -= (float) 0.1f * diffY;
	//}
	// Right Mouse Button this movement has to be stopped
	//else if ( nFlags & MK_RBUTTON)
	//{
	//	m_fPosX += (float)diffX;
	//	m_fPosY -= (float)diffY;
	//}
	else
	{
		CVector3D unitVec = rayCast[1] - rayCast[0];
		CVector3D unitPow = unitVec^2.0f;
		float Len = (float)sqrt(unitPow.x + unitPow.y + unitPow.z);
		rayCast[2] = unitVec / Len;
		
		bool hit = line.HitTest(rayCast, 15.0f);

		if ( hit == TRUE)
			m_CurrentTool = Point_Sel;
		else 
			m_CurrentTool = Camera;
	}
	OnDraw(NULL);
	CWnd::OnMouseMove(nFlags, point);
}

void CLineEditControl::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(m_CurrentTool == Camera)
	{
		if(line.m_iAddRem == Points_Add)
		{
			//check our line object for hits
			GLint viewport[4];
			glGetIntegerv (GL_VIEWPORT, viewport);
	
			float realy = (float)viewport[3] - (GLint) point.y - 1;
			CVector3D rayCast[3];

			rayCast[0].x = (float)point.x;
			rayCast[0].y = realy;
			rayCast[0].z = 0.0f;

			line.addPoint(rayCast[0]);
		}
	}
	if(m_CurrentTool == Point_Sel)
	{	
		if(line.m_iAddRem == Points_Remove)
		{
			if(line.m_iVertID != NULL)
			{
				line.removePoint();
			}
		}
	}

	CWnd::OnLButtonDown(nFlags, point);
}

void CLineEditControl::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnLButtonUp(nFlags, point);
}
