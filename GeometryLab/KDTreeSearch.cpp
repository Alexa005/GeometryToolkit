#include <iostream>
#include <vector>

#include "Point.h"
#include "KDTree.h"

void runKDTreeSearch()
{
    int n;

    std::cout << "Enter the number of points: ";

    if (!(std::cin >> n) || n < 0)
    {
        std::cout << "Error: invalid number of points.\n";
        return;
    }

    KDTree tree;

    std::cout << "Enter the coordinates of the points (x y):\n";

    for (int i = 0; i < n; ++i)
    {
        double x, y;

        if (!(std::cin >> x >> y))
        {
            std::cout << "Error: invalid point coordinates.\n";
            return;
        }

        if (!tree.insert(Point(x, y)))
        {
            std::cout << "Duplicate point ignored: "
                << x << ' ' << y << '\n';
        }
    }

    double x1, y1, x2, y2;

    std::cout << "Enter the rectangle boundaries "
        << "(left bottom x y, right top x y): ";

    if (!(std::cin >> x1 >> y1 >> x2 >> y2))
    {
        std::cout << "Error: invalid rectangle coordinates.\n";
        return;
    }

    if (x1 > x2 || y1 > y2)
    {
        std::cout << "Error: invalid rectangle boundaries.\n";
        return;
    }

    const std::vector<Point> found =
        tree.rangeSearch(Point(x1, y1), Point(x2, y2));

    std::cout << "Points inside the rectangle: "
        << found.size() << '\n';

    for (const Point& point : found)
    {
        std::cout << point.x << ' '
            << point.y << '\n';
    }

    double qx, qy;

    std::cout << "Enter a point to search for (x y): ";

    if (!(std::cin >> qx >> qy))
    {
        std::cout << "Error: invalid point coordinates.\n";
        return;
    }

    if (tree.contains(Point(qx, qy)))
    {
        std::cout << "The point exists in the tree.\n";
    }
    else
    {
        std::cout << "The point does not exist in the tree.\n";
    }
}