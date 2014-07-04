#include"PanelD.h"

PanelD::PanelD(wxWindow * parent):wxPanel(parent)
{
        pg = new wxPropertyGrid(
        this, // parent
        wxID_ANY, // id
        wxDefaultPosition, // position
        wxDefaultSize, // size
        // Here are just some of the supported window styles
        wxPG_SPLITTER_AUTO_CENTER | // Automatically center splitter until user manually adjusts it
        // Default style
        wxPG_DEFAULT_STYLE );
    sizer = new wxBoxSizer(wxVERTICAL);
}

void PanelD::SetUpGUI()
{
    pg->Append( new wxIntProperty("Form_code", "Name", 9999) );
    pg->Append( new wxStringProperty("Field name", wxPG_LABEL) );
    pg->Append( new wxIntProperty("PDF Page No", wxPG_LABEL) );
    pg->Append( new wxIntProperty("X pos", wxPG_LABEL) );
    pg->Append( new wxIntProperty("Y pos", wxPG_LABEL) );
    pg->Append( new wxIntProperty("width", wxPG_LABEL) );
    pg->Append( new wxIntProperty("height", wxPG_LABEL) );
    pg->Append( new wxStringProperty("Font", wxPG_LABEL) );
    pg->Append( new wxIntProperty("Font Size", wxPG_LABEL) );
    pg->Append( new wxIntProperty("num of char", wxPG_LABEL) );
    const wxChar* arr1[] ={ wxT("Center"), wxT("Left"), wxT("Right"), NULL };
    pg->Append( new wxEnumProperty("Align",
                               wxPG_LABEL,
                               arr1) );

    const wxChar* arr2[] ={ wxT("Number"), wxT("RTL"), wxT("LTR"), NULL };
    pg->Append( new wxEnumProperty("Field Type",
                               wxPG_LABEL,
                               arr2) );
    sizer->Add(pg,0,wxEXPAND,0);
    SetSizer(sizer);
}
