#include <iostream>

#include "Geometry.h"
#include "Point.h"

void runPointInAngleCheck()
{
    std::cout << "Check if point A lies inside the angle BCD\n";
    std::cout << "(the angle swept from CB to CD counterclockwise)\n\n";

    Point a, b, c, d;

    std::cout << "Enter point A (x y): ";
    std::cin >> a.x >> a.y;

    std::cout << "Enter point B (x y): ";
    std::cin >> b.x >> b.y;

    std::cout << "Enter point C (x y): ";
    std::cin >> c.x >> c.y;

    std::cout << "Enter point D (x y): ";
    std::cin >> d.x >> d.y;

    const bool inside = Geometry::isInsideAngle(a, b, c, d);

    if (inside)
        std::cout << "\nPoint A lies inside the angle BCD.\n";
    else
        std::cout << "\nPoint A does not lie inside the angle BCD.\n";
}