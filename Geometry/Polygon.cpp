#include "Polygon.h"
#include "Geometry.h"
#include "Line.h"

#include <algorithm>
#include <cmath>
#include <utility>

namespace
{
    // --- Разбиение рёбер ---

    std::vector<Point> collectSplitPoints(
        const Segment& edge,
        const Polygon& other)
    {
        std::vector<Point> points;
        points.push_back(edge.start);
        points.push_back(edge.end);

        for (std::size_t i = 0; i < other.size(); ++i)
        {
            const Segment otherEdge = other.getEdge(i);

            if (!Geometry::segmentsIntersect(edge, otherEdge))
            {
                continue;
            }

            if (Geometry::pointOnSegment(otherEdge.start, edge))
            {
                points.push_back(otherEdge.start);
            }
            if (Geometry::pointOnSegment(otherEdge.end, edge))
            {
                points.push_back(otherEdge.end);
            }

            Point cross;
            if (Geometry::lineIntersection(
                Line(edge.start, edge.end),
                Line(otherEdge.start, otherEdge.end),
                cross) &&
                Geometry::pointOnSegment(cross, edge) &&
                Geometry::pointOnSegment(cross, otherEdge))
            {
                points.push_back(cross);
            }
        }

        return points;
    }

    std::vector<Segment> splitEdge(
        const Segment& edge,
        const std::vector<Point>& points)
    {
        std::vector<std::pair<double, Point>> sorted;
        sorted.reserve(points.size());

        for (const Point& p : points)
        {
            sorted.emplace_back(edge.start.distanceTo(p), p);
        }

        std::sort(
            sorted.begin(),
            sorted.end(),
            [](const auto& a, const auto& b)
            {
                return a.first < b.first;
            });

        std::vector<Point> unique;
        for (const auto& entry : sorted)
        {
            const Point& p = entry.second;

            bool duplicate = false;
            for (const Point& q : unique)
            {
                if (q == p)
                {
                    duplicate = true;
                    break;
                }
            }

            if (!duplicate)
            {
                unique.push_back(p);
            }
        }

        std::vector<Segment> result;
        for (std::size_t i = 0; i + 1 < unique.size(); ++i)
        {
            result.emplace_back(unique[i], unique[i + 1]);
        }

        return result;
    }

    std::vector<Segment> splitAllEdges(
        const Polygon& poly,
        const Polygon& other)
    {
        std::vector<Segment> pieces;

        for (std::size_t i = 0; i < poly.size(); ++i)
        {
            const Segment edge = poly.getEdge(i);
            const std::vector<Point> points = collectSplitPoints(edge, other);
            const std::vector<Segment> parts = splitEdge(edge, points);

            pieces.insert(pieces.end(), parts.begin(), parts.end());
        }

        return pieces;
    }

    // --- Дедупликация и склейка ---

    std::vector<Segment> deduplicate(const std::vector<Segment>& segments)
    {
        std::vector<Segment> unique;

        for (const Segment& s : segments)
        {
            bool duplicate = false;
            for (const Segment& t : unique)
            {
                if ((s.start == t.start && s.end == t.end) ||
                    (s.start == t.end && s.end == t.start))
                {
                    duplicate = true;
                    break;
                }
            }

            if (!duplicate)
            {
                unique.push_back(s);
            }
        }

        return unique;
    }

    std::vector<std::vector<Point>> chainIntoLoops(
        const std::vector<Segment>& segments)
    {
        std::vector<std::vector<Point>> loops;
        std::vector<bool> used(segments.size(), false);

        for (std::size_t i = 0; i < segments.size(); ++i)
        {
            if (used[i])
            {
                continue;
            }

            std::vector<Point> loop;
            const Point startPoint = segments[i].start;

            used[i] = true;
            loop.push_back(startPoint);

            Point current = segments[i].end;
            bool closed = false;

            while (true)
            {
                if (current == startPoint)
                {
                    closed = true;
                    break;
                }

                loop.push_back(current);

                bool found = false;
                for (std::size_t j = 0; j < segments.size(); ++j)
                {
                    if (used[j])
                    {
                        continue;
                    }
                    if (segments[j].start == current)
                    {
                        used[j] = true;
                        current = segments[j].end;
                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    break;
                }
            }

            if (closed && loop.size() >= 3)
            {
                loops.push_back(loop);
            }
        }

        return loops;
    }
}

// ---------------------------------------------------------------------------
// Polygon
// ---------------------------------------------------------------------------

Polygon::Polygon()
{
}

Polygon::Polygon(const std::vector<Point>& vertices)
    : vertices(vertices)
{
}

std::size_t Polygon::size() const
{
    return vertices.size();
}

Segment Polygon::getEdge(std::size_t index) const
{
    const std::size_t next = (index + 1) % vertices.size();

    return Segment(vertices[index], vertices[next]);
}

// --- Метрики и ориентация ---

double Polygon::signedArea() const
{
    double area = 0.0;
    const std::size_t n = vertices.size();

    for (std::size_t i = 0; i < n; ++i)
    {
        const Point& a = vertices[i];
        const Point& b = vertices[(i + 1) % n];

        area += a.x * b.y - b.x * a.y;
    }

    return area * 0.5;
}

double Polygon::area() const
{
    return std::abs(signedArea());
}

bool Polygon::isCCW() const
{
    return signedArea() > 0.0;
}

Polygon Polygon::asCCW() const
{
    if (isCCW() || vertices.size() < 3)
    {
        return *this;
    }

    std::vector<Point> reversed;
    reversed.reserve(vertices.size());

    for (std::size_t i = vertices.size(); i > 0; --i)
    {
        reversed.push_back(vertices[i - 1]);
    }

    return Polygon(reversed);
}

// --- Принадлежность точки ---

bool Polygon::containsOnBoundary(const Point& p) const
{
    for (std::size_t i = 0; i < size(); ++i)
    {
        if (Geometry::pointOnSegment(p, getEdge(i)))
        {
            return true;
        }
    }
    return false;
}

bool Polygon::contains(const Point& p) const
{
    // Точка на границе — не "строго внутри".
    if (containsOnBoundary(p))
    {
        return false;
    }

    bool inside = false;
    const std::size_t n = size();

    for (std::size_t i = 0, j = n - 1; i < n; j = i++)
    {
        const Point& a = vertices[i];
        const Point& b = vertices[j];

        const bool crosses =
            ((a.y > p.y) != (b.y > p.y)) &&
            (p.x < (b.x - a.x) * (p.y - a.y) / (b.y - a.y) + a.x);

        if (crosses)
        {
            inside = !inside;
        }
    }

    return inside;
}

bool Polygon::containsOrOnBoundary(const Point& p) const
{
    return contains(p) || containsOnBoundary(p);
}

// --- Простота ---

bool Polygon::isSimple() const
{
    const std::size_t n = vertices.size();

    if (n < 3)
    {
        return false;
    }

    for (std::size_t i = 0; i < n; ++i)
    {
        const Segment first = getEdge(i);

        for (std::size_t j = i + 1; j < n; ++j)
        {
            if (j == i + 1 || (i == 0 && j == n - 1))
            {
                continue;
            }

            const Segment second = getEdge(j);

            if (Geometry::segmentsIntersect(first, second))
            {
                return false;
            }
        }
    }

    return true;
}

// --- Пересечение ---

std::vector<Polygon> Polygon::intersect(const Polygon& other) const
{
    const Polygon p1 = asCCW();
    const Polygon p2 = other.asCCW();

    // 1. Разбить рёбра в точках пересечения.
    const std::vector<Segment> pieces1 = splitAllEdges(p1, p2);
    const std::vector<Segment> pieces2 = splitAllEdges(p2, p1);

    // 2. Отфильтровать куски, лежащие внутри или на границе другого.
    std::vector<Segment> boundary;

    for (const Segment& s : pieces1)
    {
        if (p2.containsOrOnBoundary(s.midpoint()))
        {
            boundary.push_back(s);
        }
    }

    for (const Segment& s : pieces2)
    {
        if (p1.containsOrOnBoundary(s.midpoint()))
        {
            boundary.push_back(s);
        }
    }

    // 3. Дедупликация коллинеарных наложений.
    boundary = deduplicate(boundary);

    // 4. Склейка в замкнутые контуры.
    const std::vector<std::vector<Point>> loops = chainIntoLoops(boundary);

    std::vector<Polygon> result;
    result.reserve(loops.size());

    for (const std::vector<Point>& loop : loops)
    {
        result.emplace_back(loop);
    }

    return result;
}

bool Polygon::isConvex() const
{
    const std::size_t n = vertices.size();

    // Многоугольник с менее чем 3 вершинами считаем выпуклым по соглашению.
    if (n < 3)
    {
        return true;
    }

    bool hasPositive = false;
    bool hasNegative = false;

    for (std::size_t i = 0; i < n; ++i)
    {
        const Point& a = vertices[i];
        const Point& b = vertices[(i + 1) % n];
        const Point& c = vertices[(i + 2) % n];

        const Orientation current = Geometry::orientation(a, b, c);

        if (current == Orientation::CounterClockwise)
        {
            hasPositive = true;
        }
        else if (current == Orientation::Clockwise)
        {
            hasNegative = true;
        }

        // Если встретились повороты в обе стороны — многоугольник невыпуклый.
        if (hasPositive && hasNegative)
        {
            return false;
        }
    }

    // Все точки коллинеарны — по соглашению считаем выпуклым.
    return true;
}