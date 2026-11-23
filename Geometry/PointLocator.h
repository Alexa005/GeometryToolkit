#pragma once

#include "Point.h"
#include "PlanarGraph.h"
#include "StripDecomposition.h"
#include "Trapezoid.h"

enum class PointLocation
{
    Inside,
    Boundary,
    Outside
};

struct PointLocationResult
{
    PointLocation location;
    const Trapezoid* trapezoid;

    PointLocationResult(
        PointLocation location,
        const Trapezoid* trapezoid = nullptr
    )
        : location(location),
        trapezoid(trapezoid)
    {
    }
};

class PointLocator
{
public:
    PointLocator(
        const PlanarGraph& graph,
        const StripDecomposition& decomposition
    );

    PointLocationResult locate(const Point& point) const;

private:
    const PlanarGraph& graph;
    const StripDecomposition& decomposition;
};