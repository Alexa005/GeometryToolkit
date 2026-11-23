#pragma once
#include "Point.h"
#include "Line.h"
#include "Segment.h"

#include <vector>

enum class Orientation
{
    Collinear,
    Clockwise,
    CounterClockwise
};

class Geometry
{
public:
    static Orientation orientation(
        const Point& a,
        const Point& b,
        const Point& c
    );

    static bool areCollinear(
        const Point& a,
        const Point& b,
        const Point& c
    );

    static bool pointOnSegment(
        const Point& point,
        const Segment& segment
    );

    static bool segmentsIntersect(
        const Segment& first,
        const Segment& second
    );

    static bool lineIntersection(
        const Line& first,
        const Line& second,
        Point& intersection
    );

    static char whichPointIsBetween(
        const Point& a,
        const Point& b,
        const Point& c
    );

    static bool isInsideAngle(
        const Point& a,
        const Point& b,
        const Point& c,
        const Point& d
    );

};