#include "stdafx.h"
#include "OpenGLControl.h"


BEGIN_MESSAGE_MAP(COpenGLControl, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

COpenGLControl::COpenGLControl(void)
{
}


COpenGLControl::~COpenGLControl(void)
{
}

void COpenGLControl::oglCreate(CRect rect, CWnd *parent)
{
	CString	className = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_OWNDC, NULL,
											(HBRUSH)GetStockObject(BLACK_BRUSH), NULL);

	CString oglName = CString(_T("OpenGL"));

	CreateEx(0, className, oglName, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, rect, parent, 0);

	// Set initial variables' values
	m_oldWindow		= rect;
	m_originalRect	= rect;

	hWnd = parent;
}

 void COpenGLControl::OnPaint()
 {
	//CPaintDC dc(this);	//device context for painting
	ValidateRect(NULL);
 }

 int COpenGLControl::OnCreate(LPCREATESTRUCT lpCreateStruct)
 {
	 if (CWnd::OnCreate(lpCreateStruct) == -1)
		 return -1;

	 oglInitialize();

	 return 0;
 }

 void COpenGLControl::oglInitialize(void)
 {
	 // Initial Setup
	 //
	 static PIXELFORMATDESCRIPTOR pfd =
	 {
		 sizeof(PIXELFORMATDESCRIPTOR),
		 1,
		 PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		 PFD_TYPE_RGBA,
		 32,		// bit depth
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		 16, // z-buffer depth
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

	 // Basic Setup:
	 //
	 // Set color to use when clearing the background.
	 glClearColor(0.0, 0.0, 1.0f, 1.0f);
	 glClearDepth(1.0f);


	 glFrontFace(GL_CCW);	// set the winding order to counter clockwise ( which should be on by default)
	 glCullFace(GL_BACK);	// Turn on backface culling

	 //Turn on depth testing
	 glEnable(GL_DEPTH_TEST);
	 glDepthFunc(GL_LEQUAL);

	 // Send draw request
	 //OnDraw(NULL);
 }