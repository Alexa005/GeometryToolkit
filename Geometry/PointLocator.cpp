#include "PointLocator.h"
#include "Geometry.h"

#include <algorithm>
#include <cmath>

namespace
{
    const double EPSILON = 1e-9;

    bool isFinitePoint(const Point& point)
    {
        return std::isfinite(point.x) &&
            std::isfinite(point.y);
    }

    bool pointOnAnyEdge(
        const PlanarGraph& graph,
        const Point& point
    )
    {
        const auto& vertices = graph.getVertices();
        const auto& edges = graph.getEdges();

        for (const Edge& edge : edges)
        {
            if (Geometry::pointOnSegment(
                point, Segment(
                vertices[edge.first],
                vertices[edge.second])))
            {
                return true;
            }
        }

        return false;
    }

    bool pointInsideGraph(
        const PlanarGraph& graph,
        const Point& point
    )
    {
        int intersections = 0;

        const auto& vertices = graph.getVertices();
        const auto& edges = graph.getEdges();

        for (const Edge& edge : edges)
        {
            const Point& a = vertices[edge.first];
            const Point& b = vertices[edge.second];

            // Игнорируем горизонтальные рёбра
            // и рёбра, не пересекающие уровень точки.
            if ((a.y > point.y) == (b.y > point.y))
            {
                continue;
            }

            const double intersectionX =
                a.x + (b.x - a.x) *
                ((point.y - a.y) / (b.y - a.y));

            if (intersectionX > point.x)
            {
                ++intersections;
            }
        }

        return intersections % 2 == 1;
    }

    double getEdgeXAtY(
        const PlanarGraph& graph,
        int edgeIndex,
        double y
    )
    {
        const Edge& edge = graph.getEdges()[edgeIndex];

        const Point& a = graph.getVertices()[edge.first];
        const Point& b = graph.getVertices()[edge.second];

        return a.x + (b.x - a.x) *
            ((y - a.y) / (b.y - a.y));
    }

    const Trapezoid* findCell(
        const StripDecomposition& decomposition,
        const PlanarGraph& graph,
        const Point& point
    )
    {
        const auto& strips = decomposition.getStrips();

        for (const HorizontalStrip& strip : strips)
        {
            if (point.y < strip.getLowerY() - EPSILON ||
                point.y > strip.getUpperY() + EPSILON)
            {
                continue;
            }

            const auto& cells = strip.getCells();

            for (const StripCell& cell : cells)
            {
                const double leftX = getEdgeXAtY(
                    graph,
                    cell.leftEdgeIndex,
                    point.y
                );

                const double rightX = getEdgeXAtY(
                    graph,
                    cell.rightEdgeIndex,
                    point.y
                );

                if (point.x >= leftX - EPSILON &&
                    point.x <= rightX + EPSILON)
                {
                    return &cell.trapezoid;
                }
            }
        }

        return nullptr;
    }
}

PointLocator::PointLocator(
    const PlanarGraph& graph,
    const StripDecomposition& decomposition
)
    : graph(graph),
    decomposition(decomposition)
{
}

PointLocationResult PointLocator::locate(
    const Point& point
) const
{
    if (!graph.isValid() ||
        !decomposition.isValid() ||
        !isFinitePoint(point))
    {
        return PointLocationResult(PointLocation::Outside);
    }

    if (pointOnAnyEdge(graph, point))
    {
        return PointLocationResult(PointLocation::Boundary);
    }

    if (!pointInsideGraph(graph, point))
    {
        return PointLocationResult(PointLocation::Outside);
    }

    const Trapezoid* trapezoid =
        findCell(decomposition, graph, point);

    if (trapezoid == nullptr)
    {
        // Точка классифицирована как внутренняя,
        // но декомпозиция не нашла для неё ячейку.
        // Не выдаём некорректный результат Inside.
        return PointLocationResult(PointLocation::Outside);
    }

    return PointLocationResult(
        PointLocation::Inside,
        trapezoid
    );
}