#include <iostream>
#include <vector>

#include "Polygon.h"

namespace
{
    Polygon readPolygon(const char* label)
    {
        std::size_t n = 0;
        std::cout << "Enter number of vertices of the " << label << " polygon: ";
        std::cin >> n;

        std::vector<Point> vertices;
        vertices.reserve(n);

        std::cout << "Enter " << n << " vertices (x y):" << std::endl;
        for (std::size_t i = 0; i < n; ++i)
        {
            double x = 0.0;
            double y = 0.0;
            std::cin >> x >> y;
            vertices.push_back(Point(x, y));
        }

        return Polygon(vertices);
    }

    void printPolygon(const Polygon& poly, std::size_t index)
    {
        std::cout << "Loop #" << index << ": ";
        for (const Point& p : poly.vertices)
        {
            std::cout << "(" << p.x << ", " << p.y << ") ";
        }
        std::cout << std::endl;
    }
}

void runPolygonIntersection()
{
    std::cout << std::endl;
    std::cout << "Find intersection of two polygons" << std::endl;
    std::cout << std::endl;

    const Polygon poly1 = readPolygon("first");

    if (poly1.size() < 3)
    {
        std::cout << "A polygon must have at least 3 vertices." << std::endl;
        return;
    }

    const Polygon poly2 = readPolygon("second");

    if (poly2.size() < 3)
    {
        std::cout << "A polygon must have at least 3 vertices." << std::endl;
        return;
    }

    const std::vector<Polygon> parts = poly1.intersect(poly2);

    std::cout << std::endl;

    if (parts.empty())
    {
        std::cout << "Polygons do not intersect." << std::endl;
        return;
    }

    std::cout << "Intersection polygon(s):" << std::endl;

    for (std::size_t i = 0; i < parts.size(); ++i)
    {
        printPolygon(parts[i], i + 1);
    }
}