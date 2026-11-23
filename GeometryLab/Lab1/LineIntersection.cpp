#include <iostream>
#include <fstream>
#include <iomanip>

#include "Geometry.h"

void runLineIntersection()
{
    std::ifstream input("input.txt");

    if (!input.is_open())
    {
        std::cout << "Error: input.txt was not found." << std::endl;
        return;
    }

    std::cout << "File input.txt found." << std::endl;

    std::ofstream output("output.txt");

    if (!output.is_open())
    {
        std::cout << "Error: cannot create output.txt." << std::endl;
        return;
    }

    double x1, y1;
    double x2, y2;
    double x3, y3;
    double x4, y4;

    input >> x1 >> y1;
    input >> x2 >> y2;
    input >> x3 >> y3;
    input >> x4 >> y4;

    Point a(x1, y1);
    Point b(x2, y2);
    Point c(x3, y3);
    Point d(x4, y4);

    Line first(a, b);
    Line second(c, d);

    Point intersection;

    if (Geometry::lineIntersection(first, second, intersection))
    {
        output << std::fixed << std::setprecision(4);
        output << intersection.x << " " << intersection.y << std::endl;

        std::cout << "Intersection point has been found." << std::endl;
        std::cout << "Result has been written to output.txt." << std::endl;
    }
    else
    {
        output << "The lines do not have a single intersection point." << std::endl;

        std::cout << "The lines are parallel or coincident." << std::endl;
        std::cout << "Result has been written to output.txt." << std::endl;
    }
}