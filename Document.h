#ifndef _CFIELDADD_H
#define _CFIELDADD_H

#include<wx/wx.h>

#include <wx/bitmap.h>

#include<wx/rawbmp.h>

#include<wx/pdfdocument.h>

#include<vector>

#include"Utility.h"

#include"Main.h"

#include <wx/gdicmn.h>

#include"Grid.h"

#include "Appearnce.h"

class Document
{
    typedef wxAlphaPixelData PixelData;

    //Contains all the fields on a given page
    class PageFields
    {
    public:
        //Constructor for initializing the capacity field
        PageFields():capacity(10)
        {
            fieldCount = 0;
            pageFields.reserve(capacity);
        }

        std::vector<Field> pageFields;
        int fieldCount;
        //Vector Capacity
        int capacity;
    };

    fz_context *ctx;

    //Array of Fields on all the pages
    PageFields * docFields;

    //Units moved by field in the coordinate system of muPDF
    int mUnits;

    //PDF Dimensions in units
    int pdfUnitW,pdfUnitH;

    //The Current Page Being Displayed
    int curPage;
    //The Current Zoom Level
    int curZoom;
    //Total Page Count of the Document
    int pageCount;
    //The path of the document
    char * filePath;
    //The Bitmap to be displayed
    wxBitmap * bitmap;

    //Convert pixmap to bitmap
    wxBitmap *RGBAtoBitmap(unsigned char *rgba, int w, int h);

    //Setup temporary pdf for wxPDFDOCUMENT
    void SetupPage();

    //flag for diplaying values
    bool demo;


public:
    Document(char*);
    ~Document();

    //Add Field To the Document
    void AddField(Field f);
    //Render the Document
    wxBitmap * renderPDF();
    //Loads and prepares the Page in the memory
    void LoadPage(int);

    //Get Page Count
    int getPageCount();
    //Get Current Zoom
    int getCurZoom();
    //Get Current Page
    int getCurPage();

    //Set Current Page
    void setCurPage(int);
    //Set Current Zoom
    void setCurZoom(int);

    //get pdf units
    int getPDFWidth();
    int getPDFHeight();

    void setDemo(bool);

    //Moves the field - wxPoint acts as vector specifying direction
    void MoveFields(wxPoint,std::vector<SelectedItem> &,float);

    //Returns the field selected
    Field  SelectField(wxPoint pt);

    void AlignSelectedField(Grid,std::vector<SelectedItem> &,float);
};
#endif // _CFIELDADD_H

