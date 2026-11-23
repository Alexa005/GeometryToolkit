
#include "Trapezoid.h"

Trapezoid::Trapezoid(
    const Point& bottomLeft,
    const Point& bottomRight,
    const Point& topRight,
    const Point& topLeft
)
    : bottomLeft(bottomLeft),
    bottomRight(bottomRight),
    topRight(topRight),
    topLeft(topLeft)
{
}

const Point& Trapezoid::getBottomLeft() const
{
    return bottomLeft;
}

const Point& Trapezoid::getBottomRight() const
{
    return bottomRight;
}

const Point& Trapezoid::getTopRight() const
{
    return topRight;
}

const Point& Trapezoid::getTopLeft() const
{
    return topLeft;
}
