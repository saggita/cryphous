// ドラッグアンドドロップサンプル．
// 黒い猫．
// MITライセンス．

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/dnd.h"

// ドロップ時のイベントを記述するためのクラス．
class DragDropFile : public wxFileDropTarget
{
public:
	DragDropFile(wxListBox *listBox) :
	m_listBox( listBox )
	{
	}

	// ドロップされた際の処理．これが重要．
	virtual bool OnDropFiles(wxCoord, wxCoord, const wxArrayString& filenames);

private:
	// このリストボックスにイベントを追加していく．
	wxListBox* m_listBox;
};

// 呼出もととなるメインアプリケーション．
class DragDropApp : public wxApp
{
public:
	virtual bool OnInit();
};

IMPLEMENT_APP(DragDropApp)

class DragDropFrame : public wxFrame
{
public:
	DragDropFrame();

	void OnQuit(wxCommandEvent&) { Close(true); };
	
private:
	void createMenu();

	wxListBox *m_listBox;
	
	DECLARE_EVENT_TABLE()
};

enum
{
	Menu_Quit = 1,
};

// 終了メニューのみつけておく．
BEGIN_EVENT_TABLE(DragDropFrame, wxFrame)
	EVT_MENU(Menu_Quit, DragDropFrame::OnQuit)
END_EVENT_TABLE()

// 実質DragDropFrameクラスのインスタンスを生成するだけ．
bool DragDropApp::OnInit()
{
	if ( !wxApp::OnInit() ) {
		return false;
	}

	new DragDropFrame();

	return true;
}

DragDropFrame::DragDropFrame() :
wxFrame(
	NULL,
	wxID_ANY,
	wxT("DragDrop Sample"),
	wxPoint(10, 100)
	)
{
	// コンストラクタが長くなりすぎないように別関数にまとめています．
	createMenu();
}

void DragDropFrame::createMenu()
{
	SetIcon( wxICON(sample) );

	CreateStatusBar();

	wxMenu *fileMenu = new wxMenu;
	fileMenu->Append(Menu_Quit, wxT("E&xit\tCtrl-Q"));

	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(fileMenu, wxT("&File"));

	SetMenuBar(menuBar);

	const wxString str( wxT("ここにファイルをドロップしてください．") );

	m_listBox  = new wxListBox(
		this,
		wxID_ANY,
		wxDefaultPosition,
		wxDefaultSize,
		1,
		&str,
		wxLB_HSCROLL | wxLB_ALWAYS_SB
	);

	m_listBox->SetDropTarget( new DragDropFile(m_listBox) );

	Show();
}

bool DragDropFile::OnDropFiles(wxCoord, wxCoord, const wxArrayString& filenames)
{
	const size_t howMany = filenames.GetCount();
	const wxString str = wxString::Format("ドロップされたファイル数 = %d\n", static_cast<int>(howMany) );

	m_listBox->Append(str);
	for ( size_t i = 0; i < howMany; i++ ) {
		m_listBox->Append( filenames[i] );
	}

	return true;
}
