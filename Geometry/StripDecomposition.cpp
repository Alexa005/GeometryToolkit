
#include "StripDecomposition.h"

#include <algorithm>
#include <cmath>
#include <numeric>
#include <vector>

StripDecomposition::StripDecomposition(const PlanarGraph& graph)
    : valid(false)
{
    build(graph);
}

const std::vector<HorizontalStrip>&
StripDecomposition::getStrips() const
{
    return strips;
}

bool StripDecomposition::isValid() const
{
    return valid;
}

void StripDecomposition::build(const PlanarGraph& graph)
{
    strips.clear();
    valid = false;

    if (!graph.isValid())
    {
        return;
    }

    const auto& vertices = graph.getVertices();
    const auto& edges = graph.getEdges();

    // Проверяем координаты вершин.
    for (const Point& vertex : vertices)
    {
        if (!std::isfinite(vertex.x) ||
            !std::isfinite(vertex.y))
        {
            return;
        }
    }

    // Собираем все уровни y.
    std::vector<double> yLevels;
    yLevels.reserve(vertices.size());

    for (const Point& vertex : vertices)
    {
        yLevels.push_back(vertex.y);
    }

    // Сортируем и удаляем повторяющиеся уровни.
    std::sort(yLevels.begin(), yLevels.end());

    yLevels.erase(
        std::unique(yLevels.begin(), yLevels.end()),
        yLevels.end()
    );

    // Между соседними уровнями строим полосы.
    for (std::size_t i = 0; i + 1 < yLevels.size(); ++i)
    {
        const double lowerY = yLevels[i];
        const double upperY = yLevels[i + 1];
        const double middleY = lowerY + (upperY - lowerY) / 2.0;

        std::vector<int> activeEdges;

        // Находим рёбра, проходящие через всю полосу.
        for (int edgeIndex = 0;
            edgeIndex < static_cast<int>(edges.size());
            ++edgeIndex)
        {
            const Edge& edge = edges[edgeIndex];

            const Point& first = vertices[edge.first];
            const Point& second = vertices[edge.second];

            const double minY = (std::min)(first.y, second.y);
            const double maxY = (std::max)(first.y, second.y);

            // Горизонтальные рёбра не пересекают внутренность полосы.
            if (minY <= lowerY && maxY >= upperY &&
                minY < maxY)
            {
                activeEdges.push_back(edgeIndex);
            }
        }

        // Сортируем рёбра слева направо по пересечению
        // с горизонталью посередине полосы.
        std::sort(
            activeEdges.begin(),
            activeEdges.end(),
            [&](int firstIndex, int secondIndex)
            {
                const Edge& firstEdge = edges[firstIndex];
                const Edge& secondEdge = edges[secondIndex];

                const Point& a = vertices[firstEdge.first];
                const Point& b = vertices[firstEdge.second];
                const Point& c = vertices[secondEdge.first];
                const Point& d = vertices[secondEdge.second];

                const double firstX =
                    a.x + (b.x - a.x) *
                    ((middleY - a.y) / (b.y - a.y));

                const double secondX =
                    c.x + (d.x - c.x) *
                    ((middleY - c.y) / (d.y - c.y));

                if (firstX == secondX)
                {
                    return firstIndex < secondIndex;
                }

                return firstX < secondX;
            }
        );

        strips.emplace_back(
            lowerY,
            upperY,
            activeEdges
        );
    }


    // Строим трапеции между соседними активными рёбрами.
    for (HorizontalStrip& strip : strips)
    {
        const auto& active = strip.getEdgeIndices();

        for (std::size_t i = 0; i + 1 < active.size(); ++i)
        {
            const int leftIndex = active[i];
            const int rightIndex = active[i + 1];

            const double lowerY = strip.getLowerY();
            const double upperY = strip.getUpperY();

            const double leftBottomX =
                getXAtY(graph, leftIndex, lowerY);

            const double rightBottomX =
                getXAtY(graph, rightIndex, lowerY);

            const double leftTopX =
                getXAtY(graph, leftIndex, upperY);

            const double rightTopX =
                getXAtY(graph, rightIndex, upperY);

            if (leftBottomX > rightBottomX ||
                leftTopX > rightTopX)
            {
                valid = false;
                strips.clear();
                return;
            }

            Trapezoid trapezoid(
                Point(leftBottomX, lowerY),
                Point(rightBottomX, lowerY),
                Point(rightTopX, upperY),
                Point(leftTopX, upperY)
            );

            strip.addCell(
                StripCell(trapezoid, leftIndex, rightIndex)
            );
        }
    }


    valid = true;
}
