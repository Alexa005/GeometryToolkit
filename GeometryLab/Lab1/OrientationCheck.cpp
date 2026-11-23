#include <iostream>
#include "Geometry.h"

void runOrientationCheck()
{
    double x1, y1;
    double x2, y2;
    double x3, y3;

    std::cout << "Enter point A (x y): ";
    std::cin >> x1 >> y1;

    std::cout << "Enter point B (x y): ";
    std::cin >> x2 >> y2;

    std::cout << "Enter point C (x y): ";
    std::cin >> x3 >> y3;

    Point a(x1, y1);
    Point b(x2, y2);
    Point c(x3, y3);

    Orientation result = Geometry::orientation(a, b, c);

    if (result == Orientation::Clockwise)
    {
        std::cout << "The points are in clockwise order." << std::endl;
    }
    else if (result == Orientation::CounterClockwise)
    {
        std::cout << "The points are in counterclockwise order." << std::endl;
    }
    else
    {
        std::cout << "The points are collinear." << std::endl;
    }
}