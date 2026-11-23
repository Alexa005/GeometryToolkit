#include <iostream>
#include <vector>

#include "Polygon.h"
#include "Point.h"

void runPointInPolygonCheck()
{
    std::cout << "Check if point A lies inside polygon B1B2...Bn\n\n";

    Point a;

    std::cout << "Enter point A (x y): ";
    std::cin >> a.x >> a.y;

    int n = 0;
    std::cout << "Enter number of vertices of polygon: ";
    std::cin >> n;

    std::vector<Point> vertices(n);

    std::cout << "Enter " << n << " vertices in boundary order (x y):\n";
    for (int i = 0; i < n; ++i)
    {
        std::cin >> vertices[i].x >> vertices[i].y;
    }

    Polygon polygon(vertices);

    // —читаем точку на границе принадлежащей многоугольнику.
    const bool inside = polygon.containsOrOnBoundary(a);

    if (inside)
    {
        std::cout << "\nPoint A lies inside the polygon.\n";
    }
    else
    {
        std::cout << "\nPoint A does not lie inside the polygon.\n";
    }
}