#include "wx/wxprec.h"

#ifndef WX_PRECOMP
	#include "wx/wx.h"
#endif

class FirstApp : public wxApp
{
public:
	virtual bool OnInit();
};

class FirstFrame : public wxFrame
{
public:
	FirstFrame(const wxString& title);

	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

private:
	DECLARE_EVENT_TABLE()
};

enum
{
	QUIT = wxID_EXIT,
	ABOUT = wxID_ABOUT,
};

BEGIN_EVENT_TABLE(FirstFrame, wxFrame)
	EVT_MENU(QUIT,FirstFrame::OnQuit)
	EVT_MENU(ABOUT, FirstFrame::OnAbout)
END_EVENT_TABLE()

IMPLEMENT_APP(FirstApp)

bool FirstApp::OnInit()
{
	if ( !wxApp::OnInit() ) {
		return false;
	}

	FirstFrame *frame = new FirstFrame("Title");

	frame->Show(true);

	return true;
}

FirstFrame::FirstFrame(const wxString& title) 
	: wxFrame( NULL, wxID_ANY, title )
{
	SetIcon(wxICON(sample));

	wxMenu *fileMenu = new wxMenu;

	wxMenu *helpMenu = new wxMenu;
	helpMenu->Append( ABOUT, "&About\tF1" );
	fileMenu->Append( QUIT, "E&xit\tAlt-X" );

	wxMenuBar *menuBar = new wxMenuBar();
	menuBar->Append(fileMenu, "&File");
	menuBar->Append(helpMenu, "&Help");

	SetMenuBar(menuBar);
}

void FirstFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	Close(true);
}

void FirstFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	wxMessageBox(
		"Message",
		"Caption",
		wxOK | wxICON_INFORMATION,
		this
	);
}
