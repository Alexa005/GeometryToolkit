#include <iostream>
#include <vector>

#include "Point.h"
#include "Polygon.h"

void runQuadrilateralConvexityCheck()
{
    double x1, y1;
    double x2, y2;
    double x3, y3;
    double x4, y4;

    std::cout << "Enter point A (x y): ";
    std::cin >> x1 >> y1;

    std::cout << "Enter point B (x y): ";
    std::cin >> x2 >> y2;

    std::cout << "Enter point C (x y): ";
    std::cin >> x3 >> y3;

    std::cout << "Enter point D (x y): ";
    std::cin >> x4 >> y4;

    Polygon quadrilateral({
        Point(x1, y1),
        Point(x2, y2),
        Point(x3, y3),
        Point(x4, y4)
        });

    if (quadrilateral.isConvex())
    {
        std::cout << "Quadrilateral ABCD is convex." << std::endl;
    }
    else
    {
        std::cout << "Quadrilateral ABCD is not convex." << std::endl;
    }
}