#include <iostream>
#include "Geometry.h"

void runAllSegmentIntersections()
{
    int number;
    std::cout << std::endl;
    std::cout << "Check intersection of segments" << std::endl;
    std::cout << std::endl;

    std::cout << "Enter the number of segments:\n";
    std::cin >> number;

    std::vector<Segment> segments(number);
    Point a, b;

    for (int i = 0; i < number; i++) {
        std::cout << "Enter coordinates of the " << i + 1 << " segment : " << std::endl;
        std::cout << "A(x y): ";
        std::cin >> a.x >> a.y;

        std::cout << "B(x y): ";
        std::cin >> b.x >> b.y;

        std::cout << std::endl;

        segments[i] = Segment(a, b);
    }
    int count_intersects = 0;

    for (int i = 0; i < number; i++) {
        for (int j = i + 1; j < number; j++) {
            if (Geometry::segmentsIntersect(segments[i], segments[j])) {
                std::cout << "\nSegments " << i + 1 << " and " << j + 1 << "intersect.\n";
                count_intersects++;
            }
        }
    }
    std::cout << "Число пересечений: " << count_intersects << '\n';
}