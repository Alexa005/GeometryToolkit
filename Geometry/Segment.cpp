#include "Segment.h"

Segment::Segment()
    : start(), end()
{
}

Segment::Segment(const Point& start, const Point& end)
    : start(start), end(end)
{
}

double Segment::length() const
{
    return start.distanceTo(end);
}

Point Segment::midpoint() const
{
    return Point(
        (start.x + end.x) * 0.5,
        (start.y + end.y) * 0.5
    );
}