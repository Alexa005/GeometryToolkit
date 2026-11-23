
#include "PlanarGraph.h"

PlanarGraph::PlanarGraph(
    const std::vector<Point>& vertices,
    const std::vector<Edge>& edges
)
    : vertices(vertices), edges(edges)
{
}

const std::vector<Point>& PlanarGraph::getVertices() const
{
    return vertices;
}

const std::vector<Edge>& PlanarGraph::getEdges() const
{
    return edges;
}

bool PlanarGraph::isValid() const
{
    for (const Edge& edge : edges)
    {
        if (edge.first < 0 ||
            edge.second < 0 ||
            edge.first >= static_cast<int>(vertices.size()) ||
            edge.second >= static_cast<int>(vertices.size()) ||
            edge.first == edge.second)
        {
            return false;
        }
    }

    return true;
}
