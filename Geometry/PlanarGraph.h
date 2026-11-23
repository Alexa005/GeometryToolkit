
#pragma once

#include <vector>
#include "Point.h"

struct Edge
{
    int first;
    int second;

    Edge(int first, int second)
        : first(first), second(second)
    {
    }
};

class PlanarGraph
{
public:
    PlanarGraph(
        const std::vector<Point>& vertices,
        const std::vector<Edge>& edges
    );

    const std::vector<Point>& getVertices() const;
    const std::vector<Edge>& getEdges() const;

    bool isValid() const;

private:
    std::vector<Point> vertices;
    std::vector<Edge> edges;
};
