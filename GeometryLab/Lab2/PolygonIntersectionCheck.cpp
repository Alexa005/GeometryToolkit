#include <iostream>
#include <vector>

#include "Geometry.h"
#include "Polygon.h"

void runPolygonIntersectionCheck()
{
    int n;
    int m;

    std::cout << "Check intersection of two simple polygons\n\n";

    std::cout << "Enter the number of vertices of polygon P1: ";
    std::cin >> n;

    std::vector<Point> vertices1(n);

    std::cout << "Enter the vertices of P1 in boundary order (x y):\n";
    for (int i = 0; i < n; ++i)
    {
        std::cin >> vertices1[i].x >> vertices1[i].y;
    }

    std::cout << "\nEnter the number of vertices of polygon P2: ";
    std::cin >> m;

    std::vector<Point> vertices2(m);

    std::cout << "Enter the vertices of P2 in boundary order (x y):\n";
    for (int i = 0; i < m; ++i)
    {
        std::cin >> vertices2[i].x >> vertices2[i].y;
    }

    Polygon polygon1(vertices1);
    Polygon polygon2(vertices2);

    bool intersects = false;

    // Шаг 1. Проверяем каждое ребро P1 с каждым ребром P2.
    for (std::size_t i = 0; i < polygon1.size() && !intersects; ++i)
    {
        Segment edge1 = polygon1.getEdge(i);

        for (std::size_t j = 0; j < polygon2.size(); ++j)
        {
            Segment edge2 = polygon2.getEdge(j);

            if (Geometry::segmentsIntersect(edge1, edge2))
            {
                intersects = true;
                break;
            }
        }
    }

    // Шаг 2. Если границы не пересеклись, проверяем вложенность.
    if (!intersects)
    {
        if (polygon2.containsOrOnBoundary(polygon1.vertices[0]) ||
            polygon1.containsOrOnBoundary(polygon2.vertices[0]))
        {
            intersects = true;
        }
    }

    if (intersects)
    {
        std::cout << "\nPolygons intersect.\n";
    }
    else
    {
        std::cout << "\nPolygons do not intersect.\n";
    }
}