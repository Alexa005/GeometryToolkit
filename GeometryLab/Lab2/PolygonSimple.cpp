#include <iostream>
#include <vector>

#include "Polygon.h"

void runPolygonSimplicityCheck()
{
    std::cout << "\n=== POLYGON SIMPLICITY CHECK ===\n\n";

    int n;

    std::cout << "Enter the number of vertices: ";

    if (!(std::cin >> n) || n < 3)
    {
        std::cout << "A polygon must have at least 3 vertices.\n";
        return;
    }

    std::vector<Point> vertices(n);

    std::cout << "Enter the vertices in boundary order (x y):\n";

    for (int i = 0; i < n; ++i)
    {
        if (!(std::cin >> vertices[i].x >> vertices[i].y))
        {
            std::cout << "Invalid input.\n";
            return;
        }
    }

    Polygon polygon(vertices);

    if (polygon.isSimple())
    {
        std::cout << "\nPolygon is simple.\n";
    }
    else
    {
        std::cout << "\nPolygon is not simple.\n";
    }
}