
#include <iostream>
#include <vector>

#include "Point.h"
#include "PlanarGraph.h"
#include "StripDecomposition.h"
#include "PointLocator.h"

void runPointLocation()
{
    int vertexCount;

    std::cout << "Enter the number of vertices: ";

    if (!(std::cin >> vertexCount) || vertexCount < 0)
    {
        std::cout << "Error: invalid number of vertices.\n";
        return;
    }

    std::vector<Point> vertices;
    vertices.reserve(vertexCount);

    std::cout << "Enter the coordinates of the vertices (x y):\n";

    for (int i = 0; i < vertexCount; ++i)
    {
        double x, y;

        if (!(std::cin >> x >> y))
        {
            std::cout << "Error: invalid vertex coordinates.\n";
            return;
        }

        vertices.emplace_back(x, y);
    }

    int edgeCount;

    std::cout << "Enter the number of edges: ";

    if (!(std::cin >> edgeCount) || edgeCount < 0)
    {
        std::cout << "Error: invalid number of edges.\n";
        return;
    }

    std::vector<Edge> edges;
    edges.reserve(edgeCount);

    std::cout << "Enter the indices of the endpoints of each edge:\n";

    for (int i = 0; i < edgeCount; ++i)
    {
        int first, second;

        if (!(std::cin >> first >> second))
        {
            std::cout << "Error: invalid edge input.\n";
            return;
        }

        if (first < 0 || first >= vertexCount ||
            second < 0 || second >= vertexCount)
        {
            std::cout << "Error: vertex index is out of range.\n";
            return;
        }

        edges.emplace_back(first, second);
    }

    PlanarGraph graph(vertices, edges);

    if (!graph.isValid())
    {
        std::cout << "Error: invalid graph.\n";
        return;
    }

    StripDecomposition decomposition(graph);

    if (!decomposition.isValid())
    {
        std::cout << "Error: failed to construct the strip decomposition.\n";
        return;
    }

    double x, y;

    std::cout << "Enter the coordinates of the point to locate (x y): ";

    if (!(std::cin >> x >> y))
    {
        std::cout << "Error: invalid point coordinates.\n";
        return;
    }

    PointLocator locator(graph, decomposition);
    PointLocationResult result = locator.locate(Point(x, y));

    switch (result.location)
    {
    case PointLocation::Inside:
        std::cout << "Result: the point is inside the graph.\n";

        if (result.trapezoid != nullptr)
        {
            const Trapezoid& t = *result.trapezoid;

            std::cout << "Located trapezoid:\n";

            std::cout << "Bottom-left: "
                << t.getBottomLeft().x << ' '
                << t.getBottomLeft().y << '\n';

            std::cout << "Bottom-right: "
                << t.getBottomRight().x << ' '
                << t.getBottomRight().y << '\n';

            std::cout << "Top-right: "
                << t.getTopRight().x << ' '
                << t.getTopRight().y << '\n';

            std::cout << "Top-left: "
                << t.getTopLeft().x << ' '
                << t.getTopLeft().y << '\n';
        }
        break;

    case PointLocation::Boundary:
        std::cout << "Result: the point lies on the graph boundary.\n";
        break;

    case PointLocation::Outside:
        std::cout << "Result: the point is outside the graph.\n";
        break;
    }
}