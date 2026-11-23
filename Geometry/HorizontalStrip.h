
#pragma once

#include <vector>

#include "Trapezoid.h"

struct StripCell
{
    Trapezoid trapezoid;
    int leftEdgeIndex;
    int rightEdgeIndex;

    StripCell(
        const Trapezoid& trapezoid,
        int leftEdgeIndex,
        int rightEdgeIndex
    )
        : trapezoid(trapezoid),
        leftEdgeIndex(leftEdgeIndex),
        rightEdgeIndex(rightEdgeIndex)
    {
    }
};

class HorizontalStrip
{
public:
    HorizontalStrip(
        double lowerY,
        double upperY,
        const std::vector<int>& edgeIndices
    );

    double getLowerY() const;
    double getUpperY() const;

    const std::vector<int>& getEdgeIndices() const;
    const std::vector<StripCell>& getCells() const;

    void addCell(const StripCell& cell);

    bool containsY(double y) const;
    bool isValid() const;

private:
    double lowerY;
    double upperY;

    std::vector<int> edgeIndices;
    std::vector<StripCell> cells;
};
