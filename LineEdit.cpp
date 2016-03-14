#include "stdafx.h"
#include "LineEdit.h"

BEGIN_MESSAGE_MAP(CLineEditControl, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

CLineEditControl::CLineEditControl(void)
{

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
	 glTranslatef(0.0f, 0.0f, -5.0f);
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
	glOrtho(-1.0*cx,  1.0*cx,-1.0*cy, 1.0*cy, -20, 20);

	// Model Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void CLineEditControl::oglDrawScene(void)
{
	// Wireframe Mode
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_FRONT, GL_FILL);

	glLineWidth(10.0f);
	glBegin(GL_LINES);
		glColor4ub( 000, 200, 255, 255);
		glVertex3f( 0.0f,  1.0f, 0.0f);
		glVertex3f( 2.0f,  0.0f, 0.0f);
	glEnd();
	glPointSize(15.0f);
	glBegin(GL_POINTS);
		glColor4ub( 000, 000, 002, 255);
		glVertex3f( 0.0f,  1.0f, 0.0f);
		glVertex3f( 1.0f,  1.0f, 0.0f);
	glEnd();
}

void CLineEditControl::OnMouseMove(UINT nFlags, CPoint point)
{
	int diffX = (int)(point.x - m_fLastX);
	int diffY = (int)(point.y - m_fLastY);
	m_fLastX  = (float)point.x;
	m_fLastY  = (float)point.y;


}
