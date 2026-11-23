#pragma once

struct Rectangle
{
    double minX;
    double maxX;
    double minY;
    double maxY;

    Rectangle(double minX, double maxX, double minY, double maxY)
        : minX(minX),
        maxX(maxX),
        minY(minY),
        maxY(maxY)
    {
    }

    bool isValid() const
    {
        return minX <= maxX && minY <= maxY;
    }
};
