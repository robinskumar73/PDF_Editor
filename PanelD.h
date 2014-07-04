#ifndef _PANEL_D_H
#define _PANEL_D_H
#include<wx/wx.h>
#include <wx/splitter.h>
#include <wx/sizer.h>
#include <wx/filepicker.h>
#include <wx/generic/dirctrlg.h>
#include<wx/dataview.h>
#include <wx/propgrid/propgrid.h>
class PanelD:public wxPanel
{
    wxPropertyGrid* pg;
    wxBoxSizer * sizer;
public:
    PanelD(wxWindow * parent);
    void SetUpGUI();
};
#endif // _PANEL_D_H
