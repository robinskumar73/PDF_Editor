#include<wx/wx.h>
#include <wx/splitter.h>
#include <wx/sizer.h>
#include"PanelA.h"
#include"PanelB.h"
#include"PanelC.h"
#include"PanelD.h"

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnClick(wxCommandEvent& event);
private:
    DECLARE_EVENT_TABLE();
};

DECLARE_APP(MyApp)
IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    MyFrame * frame = new MyFrame(wxT("APPLICATION"));
    frame->Show();

    return true;;
}

BEGIN_EVENT_TABLE(MyFrame,wxFrame)
    EVT_MENU(wxID_ABOUT,MyFrame::OnAbout)
    EVT_MENU(wxID_EXIT,MyFrame::OnQuit)
    EVT_BUTTON(wxID_OK,MyFrame::OnClick)
END_EVENT_TABLE()

void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg;
    msg.Printf(wxT("Hello and Welcome to %s"),wxVERSION_STRING);
    wxMessageBox(msg,wxT("AboutMinimal"),wxOK|wxICON_INFORMATION,this);
}

void MyFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void MyFrame::OnClick(wxCommandEvent& event)
{
    wxMessageBox(wxT("DDD"),wxT("0"),wxOK,0,0,0);
}

MyFrame::MyFrame(const wxString& title):wxFrame(NULL,wxID_ANY,title,wxDefaultPosition,wxDefaultSize)
{
    Maximize(true);
    int width,height;
    GetClientSize(&width,&height);
    int minWIDTH = width/7;
    int minHEIGHT = height/7;
    int defSashPos1 = width - width/5;
    int defSashPos0 = width/5;
    wxSplitterWindow * mainWindow = new wxSplitterWindow(this,wxID_ANY);
    wxSplitterWindow * subWindowV = new wxSplitterWindow(mainWindow,wxID_ANY);
    wxSplitterWindow * subWindowH = new wxSplitterWindow(mainWindow,wxID_ANY);
    subWindowH->SetSashGravity(0.7);
    subWindowV->SetSashGravity(0);
    subWindowV->SetMinimumPaneSize(minWIDTH);
    mainWindow->SetSashGravity(1);
    mainWindow->SetMinimumPaneSize(minWIDTH);
    subWindowH->SetMinimumPaneSize(minHEIGHT);
    PanelA * panelA = new PanelA(subWindowV);
    panelA->IT();
    PanelB * panelB = new PanelB(subWindowV);
    //panelB->SetMinSize(wxSize(500,NULL));
    panelB->SetUpGUI();

    PanelC * panelC = new PanelC(subWindowH);
    panelC->SetUpGUI();
    PanelD * panelD = new PanelD(subWindowH);
    panelD->SetUpGUI();
    subWindowV->SplitVertically(panelA,panelB);
    subWindowH->SplitHorizontally(panelC,panelD);
    mainWindow->SplitVertically(subWindowV,subWindowH);
    subWindowV->SetSashPosition(defSashPos0);
    mainWindow->SetSashPosition(defSashPos1);
    wxMenu * fMenu = new wxMenu;
    wxMenu * hMenu = new wxMenu;
    hMenu->Append(wxID_ABOUT,wxT("About...\tF2"),wxT("Show about Dialog"));
    fMenu->Append(wxID_EXIT,wxT("Exit\tAlt-X"),wxT("Quit This Program"));
    wxMenuBar * menuBar = new wxMenuBar();
    menuBar->Append(fMenu,wxT("File"));
    menuBar->Append(hMenu,wxT("Help"));
    SetMenuBar(menuBar);
    CreateStatusBar(2);
    SetStatusText("Welcome");
}
