
#include "HorizontalStrip.h"

#include <cmath>

HorizontalStrip::HorizontalStrip(
    double lowerY,
    double upperY,
    const std::vector<int>& edgeIndices
)
    : lowerY(lowerY),
    upperY(upperY),
    edgeIndices(edgeIndices)
{
}

double HorizontalStrip::getLowerY() const
{
    return lowerY;
}

double HorizontalStrip::getUpperY() const
{
    return upperY;
}

const std::vector<int>& HorizontalStrip::getEdgeIndices() const
{
    return edgeIndices;
}

bool HorizontalStrip::containsY(double y) const
{
    return y > lowerY && y < upperY;
}

bool HorizontalStrip::isValid() const
{
    return std::isfinite(lowerY) &&
        std::isfinite(upperY) &&
        lowerY < upperY;
}


const std::vector<StripCell>& HorizontalStrip::getCells() const
{
    return cells;
}

void HorizontalStrip::addCell(const StripCell& cell)
{
    cells.push_back(cell);
}

