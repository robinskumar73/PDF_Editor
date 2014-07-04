#include "PanelA.h"
PanelA::PanelA(wxWindow* parent):wxPanel(parent)
{
    sizer = new wxBoxSizer(wxVERTICAL);
    this->SetBackgroundColour(wxColor(130,130,130));
}

BEGIN_EVENT_TABLE(PanelA,wxPanel)
    EVT_DIRPICKER_CHANGED(wxID_ANY,PanelA::OnDirChange)
END_EVENT_TABLE()

void PanelA::IT()
{
    treeDir = new wxTreeCtrl(this,wxID_TREECTRL);
    hor = new wxBoxSizer(wxHORIZONTAL);
    //wxFilePickerCtrl *filePicker = new wxFilePickerCtrl(this, wxID_ANY, wxEmptyString, _T("Select a log file"), _T("*.*"), wxDefaultPosition, wxDefaultSize, 0);
     dirPicker = new wxDirPickerCtrl(
        this,
        wxID_ANY,
        wxGetHomeDir(),
        wxT("Choose Head Directory"),
        wxDefaultPosition,
        wxDefaultSize,
        wxDIRP_USE_TEXTCTRL);
    //txt1 = new wxTextCtrl(this,wxID_ANY,wxT("C:\\MINGW\\bin"),wxDefaultPosition, wxDefaultSize,0);
    //hor->Add(txt1,0,0,0);
    //hor->Add(dirPicker,0,wxEXPAND,0);
    sizer->Add(hor,0,0,0);
    sizer->Add(dirPicker,0,wxEXPAND,0);
    sizer->Add(treeDir,1,wxEXPAND,0);
    //sizer->Layout();
    this->SetSizer(sizer);
}

void PanelA::OnDirChange(wxFileDirPickerEvent& event)
{
    cwd = event.GetPath();
    wxTreeItemId id;
    dir.Open(cwd);
    wxFileName dirname = wxFileName::DirName( "C:\\mydir" );

    dir.GetFirst(name);
    id = treeDir->AddRoot(dir.GetNameWithSep());
    treeDir->AppendItem(id,dirname.GetFullPath());
}
