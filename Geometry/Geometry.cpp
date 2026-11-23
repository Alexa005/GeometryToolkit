#include "Geometry.h"
#include "Vector.h"
#include <cmath>

namespace
{
    const double EPS = 1e-9;
}

Orientation Geometry::orientation(
    const Point& a,
    const Point& b,
    const Point& c)
{
    Vector ab(a, b);
    Vector ac(a, c);

    double cross = ab.cross(ac);

    if (std::abs(cross) < EPS)
    {
        return Orientation::Collinear;
    }

    if (cross > 0)
    {
        return Orientation::CounterClockwise;
    }

    return Orientation::Clockwise;
}

bool Geometry::areCollinear(
    const Point& a,
    const Point& b,
    const Point& c)
{
    return orientation(a, b, c) == Orientation::Collinear;
}

bool Geometry::pointOnSegment(
    const Point& point,
    const Segment& segment)
{
    if (!areCollinear(segment.start, segment.end, point))
    {
        return false;
    }

    return point.x >= std::min(segment.start.x, segment.end.x) - EPS &&
        point.x <= std::max(segment.start.x, segment.end.x) + EPS &&
        point.y >= std::min(segment.start.y, segment.end.y) - EPS &&
        point.y <= std::max(segment.start.y, segment.end.y) + EPS;
}

bool Geometry::segmentsIntersect(
    const Segment& first,
    const Segment& second)
{
    Orientation o1 = orientation(
        first.start,
        first.end,
        second.start
    );

    Orientation o2 = orientation(
        first.start,
        first.end,
        second.end
    );

    Orientation o3 = orientation(
        second.start,
        second.end,
        first.start
    );

    Orientation o4 = orientation(
        second.start,
        second.end,
        first.end
    );

    // Обычное пересечение
    if (o1 != o2 && o3 != o4)
    {
        return true;
    }

    // Особые случаи: касание концом или перекрытие
    if (o1 == Orientation::Collinear &&
        pointOnSegment(second.start, first))
    {
        return true;
    }

    if (o2 == Orientation::Collinear &&
        pointOnSegment(second.end, first))
    {
        return true;
    }

    if (o3 == Orientation::Collinear &&
        pointOnSegment(first.start, second))
    {
        return true;
    }

    if (o4 == Orientation::Collinear &&
        pointOnSegment(first.end, second))
    {
        return true;
    }

    return false;
}

bool Geometry::lineIntersection(
    const Line& first,
    const Line& second,
    Point& intersection)
{
    const double x1 = first.p1.x;
    const double y1 = first.p1.y;

    const double x2 = first.p2.x;
    const double y2 = first.p2.y;

    const double x3 = second.p1.x;
    const double y3 = second.p1.y;

    const double x4 = second.p2.x;
    const double y4 = second.p2.y;

    const double denominator =
        (x1 - x2) * (y3 - y4) -
        (y1 - y2) * (x3 - x4);

    // Прямые параллельны или совпадают
    if (std::abs(denominator) < EPS)
    {
        return false;
    }

    const double determinant1 = x1 * y2 - y1 * x2;
    const double determinant2 = x3 * y4 - y3 * x4;

    const double x =
        (determinant1 * (x3 - x4) -
            (x1 - x2) * determinant2) / denominator;

    const double y =
        (determinant1 * (y3 - y4) -
            (y1 - y2) * determinant2) / denominator;

    intersection = Point(x, y);

    return true;
}

char Geometry::whichPointIsBetween(
    const Point& a,
    const Point& b,
    const Point& c)
{
    // Предполагается, что точки различны и коллинеарны.

    Segment ac(a, c);

    if (pointOnSegment(b, ac))
    {
        return 'B';
    }

    Segment bc(b, c);

    if (pointOnSegment(a, bc))
    {
        return 'A';
    }

    return 'C';
}

bool Geometry::isInsideAngle(const Point& a, const Point& b, const Point& c, const Point& d)
{
    const Orientation fromB = Geometry::orientation(c, b, a);
    const Orientation toD = Geometry::orientation(c, a, d);

    return fromB == Orientation::CounterClockwise &&
        toD == Orientation::CounterClockwise;
}

