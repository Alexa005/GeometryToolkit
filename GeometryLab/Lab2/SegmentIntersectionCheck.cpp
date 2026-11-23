#include <iostream>

#include "Geometry.h"

void runSegmentIntersectionCheck()
{
    Point a;
    Point b;
    Point c;
    Point d;

    std::cout << std::endl;
    std::cout << "Check intersection of two segments" << std::endl;
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

    if (Geometry::segmentsIntersect(first, second))
    {
        std::cout << std::endl;
        std::cout << "Segments intersect." << std::endl;
    }
    else
    {
        std::cout << std::endl;
        std::cout << "Segments do not intersect." << std::endl;
    }
}