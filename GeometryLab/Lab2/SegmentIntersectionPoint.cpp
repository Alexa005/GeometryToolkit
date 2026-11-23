#include <iostream>
#include <vector>

#include "Geometry.h"

void runSegmentIntersectionPoint()
{
    Point a, b, c, d;

    std::cout << std::endl;
    std::cout << "=== LABORATORY WORK #2 - TASK 6 ===" << std::endl;
    std::cout << "Find intersection of two segments" << std::endl;
    std::cout << std::endl;

    std::cout << "Enter coordinates of the first segment:" << std::endl;
    std::cout << "A(x y): ";
    std::cin >> a.x >> a.y;

    std::cout << "B(x y): ";
    std::cin >> b.x >> b.y;

    std::cout << std::endl;

    std::cout << "Enter coordinates of the second segment:" << std::endl;
    std::cout << "C(x y): ";
    std::cin >> c.x >> c.y;

    std::cout << "D(x y): ";
    std::cin >> d.x >> d.y;

    Segment first(a, b);
    Segment second(c, d);

    if (!Geometry::segmentsIntersect(first, second))
    {
        std::cout << std::endl;
        std::cout << "Segments do not intersect." << std::endl;
        return;
    }

    std::cout << std::endl;
    std::cout << "Segments intersect." << std::endl;

    Line firstLine(a, b);
    Line secondLine(c, d);

    Point intersect;

    if (Geometry::lineIntersection(firstLine, secondLine, intersect))
    {
        std::cout << "Coordinates of intersection: "
            << intersect.x << ' ' << intersect.y << '\n';
        return;
    }

    // Сюда попадаем, если отрезки коллинеарны.
    std::vector<Point> common;

    auto addIfCommon = [&](const Point& p)
        {
            if (Geometry::pointOnSegment(p, first) &&
                Geometry::pointOnSegment(p, second))
            {
                for (const Point& q : common)
                {
                    if (q == p)
                    {
                        return;
                    }
                }
                common.push_back(p);
            }
        };

    addIfCommon(a);
    addIfCommon(b);
    addIfCommon(c);
    addIfCommon(d);

    if (common.size() == 1)
    {
        std::cout << "Segments touch at point: "
            << common[0].x << ' ' << common[0].y << '\n';
    }
    else if (common.size() >= 2)
    {
        std::cout << "Segments overlap. Common part: ("
            << common[0].x << ", " << common[0].y << ") - ("
            << common[1].x << ", " << common[1].y << ")\n";
    }
    else
    {
        // Теоретически сюда попасть не должны, так как segmentsIntersect уже true.
        std::cout << "Intersection exists, but cannot be represented as a single point." << std::endl;
    }
}