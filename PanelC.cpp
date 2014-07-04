#include"PanelC.h"

BEGIN_EVENT_TABLE(PanelC, wxPanel)
EVT_DATAVIEW_ITEM_BEGIN_DRAG(wxID_ABORT,PanelC::OnLeftDown)
END_EVENT_TABLE()

PanelC::PanelC(wxWindow*parent):wxPanel(parent)
{
    vert = new wxBoxSizer(wxVERTICAL);
    hor = new wxBoxSizer(wxHORIZONTAL);
}

void PanelC::SetUpGUI()
{
    data1 = new wxDataViewListCtrl(this,wxID_ABORT);
    data1->AppendTextColumn("Field_code");
    data1->AppendTextColumn("Field_desc");
    data1->AppendTextColumn("Field_type");
    data1->AppendTextColumn("Field_size");
    data1->AppendTextColumn("Field_demo");
    wxVector<wxVariant> data;
    data.push_back( wxVariant("row 0") );
    data.push_back( wxVariant("row 1") );
    data.push_back( wxVariant("row 2") );
    data.push_back( wxVariant("row 3") );
    data.push_back( wxVariant("row 4") );
    data1->AppendItem( data );
    data.clear();
    data.push_back( wxVariant("row 12") );
    data.push_back( wxVariant("row 12") );
    data.push_back( wxVariant("row 22") );
    data.push_back( wxVariant("row 32") );
    data.push_back( wxVariant("row 42") );
    data1->AppendItem( data );
    wxButton * btn1 = new wxButton(this,wxID_ANY,wxT("ADD"));
    wxButton * btn2 = new wxButton(this,wxID_ANY,wxT("EDIT"));
    wxButton * btn3 = new wxButton(this,wxID_ANY,wxT("DELETE"));
    vert->Add(data1,1,wxEXPAND,0);
    hor->Add(btn1,1,0,1);
    hor->Add(btn2,1,0,1);
    hor->Add(btn3,1,0,1);
    vert->Add(hor,0,wxEXPAND,0);
    SetSizer(vert);
}

void PanelC::OnLeftDown(wxDataViewEvent & event)
{
    //std::cout << "dragging" << std::endl;

    wxTextDataObject dragData(wxT("D"));
    wxDropSource dragSource( this );
    dragSource.SetData( dragData );
    wxDragResult result = dragSource.DoDragDrop(true);
}

