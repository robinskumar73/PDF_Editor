#ifndef _IMG_PANEL_H
#define _IMG_PANEL_H
#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/dc.h>
#include <wx/image.h>
#include <wx/bitmap.h>
#include<wx/rawbmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <wx/dnd.h>
#include<string.h>
#include <wx/gdicmn.h>
#include <wx/utils.h>
#include"Grid.h"
#include <wx/dcbuffer.h>

#include"Document.h"
typedef wxAlphaPixelData PixelData;
class PDFPanel : public wxScrolledWindow
{
    int i1;
    int x1,y1;
    //wxPdfDocument pdf;
    int pagecount;
    int curPage;
    wxBitmap * bitmap;
    //Screen Coordinates
    int w, h;
    int scrnX,scrnY;
    //PDF Coordinates
    int pdfX,pdfY;
    //for converting screen co-od to pdf co-od
    float scale;

    //Rect of th Selected fields
    std::vector<SelectedItem> selectedItems;
    std::vector<SelectedItem>::iterator it;

    //Updates the Visual of Selected Item based on scale
    void UpdateVisualSelection(float oldScale);

    Grid grid;

    wxPen pen;
public:
    Document * doc32;
    int GetPageCount();
    PDFPanel(wxWindow*);
    void paintEvent(wxPaintEvent & evt);
    void render(wxDC& dc);
    void OnClick(wxMouseEvent &event);
    void Zoom(int);
    void ChangePage(int);
    void DropField(wxCoord x, wxCoord y,wxString data);
     //Display the values
    void displayFieldValues(bool);

    //Display Grid
    void DisplayGrid(bool);

    //Align Fields
    void AlignFields();

    //Handle Keyboard Input
    void OnKeyPressed(wxKeyEvent &event);
    DECLARE_EVENT_TABLE()
};


class temp : public wxTextDropTarget
{
    wxString text;
    PDFPanel *window;
public:
        temp(PDFPanel *);
        virtual bool OnDropText (wxCoord x, wxCoord y, const wxString &data);
};


#endif // _IMG_PANEL_H
