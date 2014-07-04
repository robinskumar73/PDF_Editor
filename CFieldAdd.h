#ifndef _CFIELDADD_H
#define _CFIELDADD_H

#include<wx/wx.h>

#include <wx/bitmap.h>

#include<wx/rawbmp.h>

#include<wx/pdfdocument.h>

#include<vector>

extern "C"
{
        #include <mupdf/fitz.h>
        #include<mupdf/pdf.h>
}


class Document
{
    typedef wxAlphaPixelData PixelData;

    enum FIELD_TYPE
    {
        TEXT_FIELD
    };
    class Field
    {
        char* name;
        FIELD_TYPE type;
        int xPos,yPos;
        int width,height;
        int pageNo;
    };

    std::vector<Field> vecFields;

    //For Adding Fields to the Document
    wxPdfDocument pdf;

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

public:
    Document(char*);
    ~Document();

    //Add Field To the Document
    void AddField(char* name,char* type,int x,int y,char* value);
    //Render the Document
    wxBitmap *renderPDF(char *filename, int pagenumber, int zoom, int rotation = 0);

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


};
#endif // _CFIELDADD_H
