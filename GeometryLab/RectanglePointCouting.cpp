#include <iostream>
#include <vector>

#include "Point.h"
#include "Rectangle.h"
#include "PointCounting.h"

void runRectanglePointCounting()
{
    int n;
    std::cout << "Количество точек: ";
    std::cin >> n;

    if (n < 0)
    {
        std::cout << "Некорректное количество точек.\n";
        return;
    }

    std::vector<Point> points;
    points.reserve(static_cast<std::size_t>(n));

    std::cout << "Введите координаты точек (x y):\n";

    for (int i = 0; i < n; ++i)
    {
        double x, y;
        std::cin >> x >> y;
        points.emplace_back(x, y);
    }

    int q;
    std::cout << "Количество прямоугольников: ";
    std::cin >> q;

    if (q < 0)
    {
        std::cout << "Некорректное количество запросов.\n";
        return;
    }

    std::vector<Rectangle> rectangles;
    rectangles.reserve(static_cast<std::size_t>(q));

    std::cout
        << "Введите границы прямоугольников "
        << "(minX maxX minY maxY):\n";

    for (int i = 0; i < q; ++i)
    {
        double minX, maxX, minY, maxY;
        std::cin >> minX >> maxX >> minY >> maxY;

        rectangles.emplace_back(minX, maxX, minY, maxY);
    }

    PointCounting counter(points);
    const std::vector<int> answers =
        counter.countRectangles(rectangles);

    std::cout << "\nРезультаты:\n";

    for (std::size_t i = 0; i < answers.size(); ++i)
    {
        std::cout << "Прямоугольник " << i + 1
            << ": " << answers[i] << '\n';
    }
}