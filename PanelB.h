#ifndef _PANEL_B_H
#define _PANEL_B_H
#include <wx/toolbar.h>
#include<wx/wx.h>
#include <wx/frame.h>
#include <wx/splitter.h>
#include <wx/sizer.h>
#include"ImgPanel.h"
#include <wx/dnd.h>
#include<wx/dataview.h>
#include <wx/utils.h>
class PanelB : public wxPanel
{
    PDFPanel * pdfRender;;
    wxBoxSizer * sizer;
    wxToolBar * toolBar;
    wxComboBox * cb1;

public:
    PanelB(wxWindow*parent);
    PanelB(){}
    void SetUpGUI();
    DECLARE_EVENT_TABLE()
    void paintEvent(wxPaintEvent & evt);
    void OnComboSelect(wxCommandEvent& event);
    void OnPageSelect(wxCommandEvent& event);
    void DropField(wxCoord,wxCoord,wxString);
    void OnDemoCheck(wxCommandEvent &event);
    void OnGridCheck(wxCommandEvent &event);
    void OnAlignButton(wxCommandEvent &event);
};
#endif // _PANEL_B_H
