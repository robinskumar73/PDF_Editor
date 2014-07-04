#ifndef _PANEL_C_H
#define _PANEL_C_H
#include<wx/wx.h>
#include <wx/splitter.h>
#include <wx/sizer.h>
#include <wx/filepicker.h>
#include <wx/generic/dirctrlg.h>
#include<wx/dataview.h>
#include <wx/dnd.h>
#include"PanelB.h"
#include"temp.h"
class PanelC:public wxPanel
{
    wxBoxSizer * vert,*hor;
public:
    wxDataViewListCtrl * data1;
    PanelC(wxWindow* parent);
    void SetUpGUI();
    void OnLeftDown(wxDataViewEvent& event);
    DECLARE_EVENT_TABLE()
};

#endif // _PANEL_C_H
