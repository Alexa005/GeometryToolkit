#pragma once

#include <vector>
#include "Point.h"
#include "Rectangle.h"

class PointCounting
{
public:
    explicit PointCounting(const std::vector<Point>& points);

    std::vector<int> countRectangles(
        const std::vector<Rectangle>& rectangles
    ) const;

private:
    std::vector<Point> points;
};
