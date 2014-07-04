#ifndef _MAIN_H
#define _MAIN_H
#include <wx/gdicmn.h>
class Field
{
public:
    Field(char*name1):name(name1){}
    Field(){}
        int id;
        char* name;
        char* value;
        int type;
        float xPos,yPos;
        int width,height;
        int pageNo;
        //unit translation done by muPDF
        float transX,transY;
};

class SelectedItem
{
public:
    SelectedItem(wxRect RECT,int ID):rect(RECT),id(ID){}
    wxRect rect;
    int id;
};
#endif // _MAIN_H
