#pragma once
#include "Point.h"

class Vector
{
public:
    double x;
    double y;

    Vector();
    Vector(double x, double y);
    Vector(const Point& from, const Point& to);

    double length() const;

    double dot(const Vector& other) const;
    double cross(const Vector& other) const;

    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(double value) const;
};