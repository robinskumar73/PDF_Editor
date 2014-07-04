#ifndef _GRID_H
#define _GRID_H
#include<wx/dc.h>
#include"Main.h"
class Grid
{
    //the height and width of the client area
    float width,height;

    //the distance between two consecutive lines
    float spacing;

    //the bounds within which fields snap to Grid Lines
    float snapBound;

    //Number of Rows and Columns
    int numRow,numCol;

    //Display grid or Not
    bool display;


public:
    //Constructor takes spacing as argument
    Grid(float Spacing,float ClientWidth,float ClientHeight,float Snap);
    Grid();

    //Draws the Grid
    void DrawGrid(wxDC &);

    //Snaps the Field to nearby Grid Line
    void SnapField(Field &,float,int);

    //Set Height of Client Area
    void SetHeight(float);
    //Set Width of Client Area
    void SetWidth(float);
    //Set Spacing
    void SetSpacing(float);
    //Set snapBound
    void SetBound(float);
    //Set display
    void SetGridDisplay(bool);

    //Get Display
    bool GetDisplay();
};
#endif // _GRID_H
