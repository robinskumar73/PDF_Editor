#include"PanelB.h"

PanelB::PanelB(wxWindow*parent):wxPanel(parent)
{
    wxInitAllImageHandlers();
    pdfRender = new PDFPanel(this);
    sizer = new wxBoxSizer(wxVERTICAL);
}

BEGIN_EVENT_TABLE(PanelB, wxPanel)
EVT_PAINT(PanelB::paintEvent)
EVT_COMBOBOX(wxID_ADD,PanelB::OnComboSelect)
EVT_COMBOBOX(wxID_ABORT,PanelB::OnPageSelect)
EVT_CHECKBOX(wxID_APPLY,PanelB::OnDemoCheck)
EVT_CHECKBOX(wxID_BOLD,PanelB::OnGridCheck)
EVT_BUTTON(wxID_CANCEL,PanelB::OnAlignButton)
END_EVENT_TABLE()

void PanelB::SetUpGUI()
{
   int numPages = pdfRender->GetPageCount();
    wxString pgChoice[numPages];
    for(int i=0;i<numPages;i++)
    {
       pgChoice[i] = wxString::Format(wxT("%i"),i+1);
    }
    wxString choice[] = {wxT("25%"),wxT("50%"),wxT("75%"),wxT("100%"),wxT("200%"),wxT("400%")};
    toolBar = new wxToolBar(this,wxID_ANY);
    wxComboBox * cb2 = new wxComboBox(toolBar,wxID_ABORT,wxT("1"),wxDefaultPosition,wxDefaultSize,numPages,pgChoice,wxCB_READONLY);
    wxCheckBox * rb1 = new wxCheckBox(toolBar,wxID_ANY,wxT("Ruler"));
    wxCheckBox * rb2 = new wxCheckBox(toolBar,wxID_APPLY,wxT("Demo"));
    wxCheckBox * rb3 = new wxCheckBox(toolBar,wxID_BOLD,wxT("Grid"));
    cb1 = new wxComboBox(toolBar,wxID_ADD,wxT("100%"),wxDefaultPosition,wxDefaultSize,6,choice,wxCB_READONLY);
    wxButton * btn1 = new wxButton(toolBar,wxID_CANCEL,wxT("ALLIGN"));
    wxButton * btn2 = new wxButton(toolBar,wxID_ANY,wxT("PRINT"));
    toolBar->AddControl(cb2,wxT("Pg.No"));
    toolBar->AddControl(rb1,wxT("Ruler"));
    toolBar->AddControl(rb2,wxT("Demo"));
    toolBar->AddControl(rb3,wxT("Grid"));
    toolBar->AddControl(cb1,wxT("Zoom"));
    toolBar->AddControl(btn1);
    toolBar->AddControl(btn2);
    toolBar->Realize();
    sizer->Add(toolBar,0,0,0);
    sizer->Add(pdfRender,1,wxALIGN_CENTER|wxEXPAND,0);
    SetSizer(sizer);
}

void PanelB::paintEvent(wxPaintEvent & evt)
{
     wxPaintDC dc(this);
     dc.SetBackground(*wxGREEN_BRUSH);
}

void PanelB::OnComboSelect(wxCommandEvent &event)
{
    pdfRender->Zoom(wxAtoi(event.GetString()));
}

void PanelB::OnPageSelect(wxCommandEvent &event)
{
    pdfRender->ChangePage(wxAtoi(event.GetString()));
}

void PanelB::OnDemoCheck(wxCommandEvent&event)
{
    pdfRender->displayFieldValues(event.IsChecked());
}

void PanelB::OnGridCheck(wxCommandEvent &event)
{
    pdfRender->DisplayGrid(event.IsChecked());
}

void PanelB::OnAlignButton(wxCommandEvent &event)
{
    pdfRender->AlignFields();
}
