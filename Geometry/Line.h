#pragma once

#include "Point.h"

class Line
{
public:
    Point p1;
    Point p2;

    Line();
    Line(const Point& p1, const Point& p2);
};