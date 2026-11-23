#pragma once

#include "Point.h"

class Segment
{
public:
    Point start;
    Point end;

    Segment();
    Segment(const Point& start, const Point& end);

    double length() const;
    Point midpoint() const;
};