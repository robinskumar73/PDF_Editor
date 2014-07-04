#ifndef _PANEL_A_H
#define _PANEL_A_H
#include<wx/wx.h>
#include <wx/splitter.h>
#include <wx/sizer.h>
#include <wx/filepicker.h>
#include "wx/generic/dirctrlg.h"
#include <wx/treectrl.h>
#include<wx/dir.h>
#include <wx/treebase.h>
class PanelA :public wxPanel
{
    wxString *name;
    wxString na;
    wxString cwd;
    wxDir dir;
    wxTreeCtrl * treeDir;
    wxTextCtrl * txt1;
    wxDirPickerCtrl * dirPicker;
    wxBoxSizer * sizer;
    wxBoxSizer * hor;
    wxButton * btn1;
    void OnDirChange(wxFileDirPickerEvent& event);
    DECLARE_EVENT_TABLE();
public:
    PanelA(wxWindow* parent);
    void IT();

};
#endif // _PANEL_A_H

