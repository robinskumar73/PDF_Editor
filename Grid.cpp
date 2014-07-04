#include"Grid.h"
Grid::Grid(float spc,float wd,float ht,float snp)
{
    display = false;
    spacing = spc;
    width = wd;
    height = ht;
    snapBound = snp;
}

Grid::Grid()
{

}

void Grid::DrawGrid(wxDC &dc)
{
    if(display)
    {
        numCol = width/spacing;
        numRow = height/spacing;
        int i = 0;
        for(i = 0;i<=numCol;i++)
        {
            dc.DrawLine(i*spacing,0,i*spacing,height);
        }
        for(i = 0;i<=numRow;i++)
        {
            dc.DrawLine(0,i*spacing,width,i*spacing);
        }
    }
}

void Grid::SnapField(Field &f,float scale,int curZoom)
{
    int i = 0;
    float scaledSpaceing = spacing*scale;
    float scaledBound = snapBound*scale;
    float oldX = f.xPos/scale;
    float oldY = f.yPos/scale;
    for(i = 0;i<=numCol;i++)
    {
        if(f.xPos < i*scaledSpaceing + scaledBound && f.xPos > i*scaledSpaceing - scaledBound)
        {
            f.xPos = i*scaledSpaceing;
            break;
        }
    }
    for(i = 0;i<=numRow;i++)
    {
        if(f.yPos < i*scaledSpaceing + scaledBound && f.yPos > i*scaledSpaceing - scaledBound)
        {
            f.yPos = i*scaledSpaceing;
            break;
        }
    }
    float newX = f.xPos/scale;
    float newY = f.yPos/scale;
    f.transX += (newX - oldX)*100/curZoom;
    f.transY += (newY - oldY)*100/curZoom;
}


void Grid::SetGridDisplay(bool val)
{
    display = val;
}

void Grid::SetHeight(float h)
{
    height = h;
}

void Grid::SetWidth(float w)
{
    width = w;
}

void Grid::SetSpacing(float spc)
{
    spacing = spc;
}

void Grid::SetBound(float bnd)
{
    snapBound = bnd;
}

bool Grid::GetDisplay()
{
    return display;
}
