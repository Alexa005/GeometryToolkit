
#pragma once

#include <vector>

#include "PlanarGraph.h"
#include "HorizontalStrip.h"
#include <algorithm>
#include <cmath>


namespace
{
    double getXAtY(
        const PlanarGraph& graph,
        int edgeIndex,
        double y
    )
    {
        const Edge& edge = graph.getEdges()[edgeIndex];

        const Point& first = graph.getVertices()[edge.first];
        const Point& second = graph.getVertices()[edge.second];

        return first.x +
            (second.x - first.x) *
            ((y - first.y) / (second.y - first.y));
    }
}



class StripDecomposition
{
public:
    explicit StripDecomposition(const PlanarGraph& graph);

    const std::vector<HorizontalStrip>& getStrips() const;

    bool isValid() const;

private:
    std::vector<HorizontalStrip> strips;
    bool valid;

    void build(const PlanarGraph& graph);
};
