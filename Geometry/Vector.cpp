#include "Vector.h"
#include <cmath>

Vector::Vector() : x(0.0), y(0.0)
{
}

Vector::Vector(double x, double y)  : x(x), y(y)
{
}

Vector::Vector(const Point& from, const Point& to)
    : x(to.x - from.x),
    y(to.y - from.y)
{
}

double Vector::length() const
{
    return std::sqrt(x * x + y * y);
}

double Vector::dot(const Vector& other) const
{
    return x * other.x + y * other.y;
}

double Vector::cross(const Vector& other) const
{
    return x * other.y - y * other.x;
}

Vector Vector::operator+(const Vector& other) const
{
    return Vector(x + other.x, y + other.y);
}

Vector Vector::operator-(const Vector& other) const
{
    return Vector(x - other.x, y - other.y);
}

Vector Vector::operator*(double value) const
{
    return Vector(x * value, y * value);
}