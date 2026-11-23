#include "Point.h"
#include <cmath>

namespace
{
    const double EPS = 1e-9;
}

Point::Point() : x(0.0), y(0.0)
{
}

Point::Point(double x, double y) : x(x), y(y)
{
}

double Point::distanceTo(const Point& other) const
{
    const double dx = x - other.x;
    const double dy = y - other.y;

    return std::sqrt(dx * dx + dy * dy);
}

bool Point::operator==(const Point& other) const
{
    return std::abs(x - other.x) < EPS &&
        std::abs(y - other.y) < EPS;
}

bool Point::operator!=(const Point& other) const
{
    return !(*this == other);
}