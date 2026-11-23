#include "Line.h"

Line::Line()
    : p1(), p2()
{
}

Line::Line(const Point& p1, const Point& p2)
    : p1(p1), p2(p2)
{
}