#pragma once

#include "Point.h"
#include "Segment.h"

#include <vector>

class Polygon
{
public:
    std::vector<Point> vertices;

    Polygon();
    Polygon(const std::vector<Point>& vertices);

    std::size_t size() const;
    Segment getEdge(std::size_t index) const;

    // --- Метрики и ориентация ---

    // Знаковая площадь: > 0 для CCW, < 0 для CW.
    double signedArea() const;

    // Модуль площади.
    double area() const;

    bool isCCW() const;

    // Возвращает копию с обходом против часовой стрелки.
    Polygon asCCW() const;

    // --- Принадлежность точки ---

    // Точка лежит на границе многоугольника.
    bool containsOnBoundary(const Point& p) const;

    // Точка строго внутри (без границы).
    bool contains(const Point& p) const;

    // Точка внутри или на границе.
    bool containsOrOnBoundary(const Point& p) const;

    // --- Свойства многоугольника ---

    bool isSimple() const;
    bool isConvex() const;

    // --- Пересечение (задача 7) ---

    // Возвращает список многоугольников — частей пересечения.
    // Пустой вектор — пересечения нет (или оно вырождено в точку/отрезок).
    std::vector<Polygon> intersect(const Polygon& other) const;
};