
#pragma once

#include "Point.h"

class Trapezoid
{
public:
    Trapezoid(
        const Point& bottomLeft,
        const Point& bottomRight,
        const Point& topRight,
        const Point& topLeft
    );

    const Point& getBottomLeft() const;
    const Point& getBottomRight() const;
    const Point& getTopRight() const;
    const Point& getTopLeft() const;

private:
    Point bottomLeft;
    Point bottomRight;
    Point topRight;
    Point topLeft;
};
