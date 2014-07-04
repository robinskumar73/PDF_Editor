#include"Utility.h"
bool IsPointInRect(wxPoint pt,wxRect rect)
{

}
bool IsPointInRect(wxPoint point,int x0,int y0,int x1,int y1)
{
    return ((point.x>x0)&&(point.x<x1)&&(point.y>y0)&&(point.y<y1));
}
