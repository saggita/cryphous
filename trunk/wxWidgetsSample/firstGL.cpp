#include "wx/wxprec.h"

#ifndef WX_PRECOMP
	#include "wx/wx.h"
#endif

#include "wx/glcanvas.h"

class FirstGLContext : public wxGLContext
{
public:
	FirstGLContext(wxGLCanvas *canvas);

	void draw(const float xangle, const float yangle);
};

class FirstGLApp : public wxApp
{
public:
	FirstGLApp() :
	m_glContext( NULL ) {
	}

	FirstGLContext& GetContext(wxGLCanvas *canvas);

	virtual bool OnInit();
	virtual int OnExit();

private:
	FirstGLContext *m_glContext;
};

class FirstGLFrame : public wxFrame
{
public:
	FirstGLFrame();

private:
	void OnClose(wxCommandEvent& event);

	DECLARE_EVENT_TABLE()
};

class FirstGLCanvas : public wxGLCanvas
{
public:
	FirstGLCanvas(wxWindow *parent, int *attribList = NULL);

private:
	void OnPaint(wxPaintEvent& event);
	void OnKeyDown(wxKeyEvent& event);

	void rotate(float xangle, float yangle);

private:
	float m_xangle;
	float m_yangle;

    DECLARE_EVENT_TABLE()
};

enum
{
	NEW_STEREO_WINDOW = wxID_HIGHEST + 1
};

FirstGLContext::FirstGLContext(wxGLCanvas *canvas)
	: wxGLContext(canvas)
{
	SetCurrent(*canvas);

	glEnable( GL_DEPTH_TEST );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glFrustum( -0.5f, 0.5f, -0.5f, 0.5f, 1.0f, 3.0f );
}

void FirstGLContext::draw(float xangle, float yangle)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -2.0f);
	glRotatef(xangle, 1.0f, 0.0f, 0.0f);
	glRotatef(yangle, 0.0f, 1.0f, 0.0f);

	glBegin(GL_QUADS);
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glVertex3f( 0.5f, 0.5f, 0.5f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glVertex3f(-0.5f,-0.5f, 0.5f);
		glVertex3f( 0.5f,-0.5f, 0.5f);
	glEnd();

	glFlush();
}

IMPLEMENT_APP(FirstGLApp)

bool FirstGLApp::OnInit()
{
	if ( !wxApp::OnInit() ) {
		return false;
	}

	new FirstGLFrame();

	return true;
}

int FirstGLApp::OnExit()
{
	delete m_glContext;

	return wxApp::OnExit();
}

FirstGLContext& FirstGLApp::GetContext(wxGLCanvas *canvas)
{
	FirstGLContext *glContext;
	if ( !m_glContext ) {
		m_glContext = new FirstGLContext(canvas);
	}
	glContext = m_glContext;

	glContext->SetCurrent(*canvas);

	return *glContext;
}

BEGIN_EVENT_TABLE(FirstGLCanvas, wxGLCanvas)
	EVT_PAINT(FirstGLCanvas::OnPaint)
	EVT_KEY_DOWN(FirstGLCanvas::OnKeyDown)
END_EVENT_TABLE()

FirstGLCanvas::FirstGLCanvas(wxWindow *parent, int *attribList)
:wxGLCanvas(parent, wxID_ANY, attribList, wxDefaultPosition, wxDefaultSize,wxFULL_REPAINT_ON_RESIZE),
m_xangle( 30.0 ),
m_yangle( 30.0 )
{
}

void FirstGLCanvas::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	wxPaintDC dc(this);

	const wxSize size = GetClientSize();

	FirstGLContext& canvas = wxGetApp().GetContext(this);
	glViewport(0, 0, size.x, size.y );

	canvas.draw( m_xangle, m_yangle );

	SwapBuffers();
}

void FirstGLCanvas::rotate(const float xangle, const float yangle)
{
	m_xangle += xangle;
	m_yangle += yangle;

	Refresh(false);
}

void FirstGLCanvas::OnKeyDown(wxKeyEvent& event)
{
	const float angle = 5.0;

	switch ( event.GetKeyCode() ) {
	case WXK_RIGHT:
		rotate( 0.0, -angle );
		break;
	case WXK_LEFT:
		rotate( 0.0, angle );
		break;
	case WXK_DOWN:
		rotate( -angle, 0.0 );
		break;
	case WXK_UP:
		rotate( angle, 0.0 );
		break;
	default:
		event.Skip();
		return;
	}
}

BEGIN_EVENT_TABLE(FirstGLFrame, wxFrame)
	EVT_MENU(wxID_CLOSE, FirstGLFrame::OnClose)
END_EVENT_TABLE()

 FirstGLFrame::FirstGLFrame()
 : wxFrame(NULL, wxID_ANY, wxT("First OpenGL"))
{
	new FirstGLCanvas( this, NULL );

	SetIcon(wxICON(sample));

	wxMenu *menu = new wxMenu;
	menu->Append( wxID_CLOSE );

	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append( menu, wxT("&File") );

	SetMenuBar( menuBar );

	CreateStatusBar();

	SetClientSize(512, 512);

	Show();
}

void FirstGLFrame::OnClose(wxCommandEvent& WXUNUSED(event))
{
	Close(true);
}