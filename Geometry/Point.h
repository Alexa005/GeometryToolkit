#pragma once

class Point
{
public:
    double x;
    double y;

    Point();
    Point(double x, double y);

    double distanceTo(const Point& other) const;

    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;
};