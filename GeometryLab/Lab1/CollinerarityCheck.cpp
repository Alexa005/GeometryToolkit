#include <iostream>
#include "Geometry.h"

void runCollinearityCheck()
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

    if (Geometry::areCollinear(a, b, c))
    {
        std::cout << "Points are collinear." << std::endl;
    }
    else
    {
        std::cout << "Points are not collinear." << std::endl;
    }
}