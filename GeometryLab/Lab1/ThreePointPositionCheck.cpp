#include <iostream>
#include <fstream>

#include "Geometry.h"

void runThreePointPositionCheck()
{
    std::ifstream input("input1.txt");

    if (!input.is_open())
    {
        std::cout << "Error: input1.txt was not found." << std::endl;
        return;
    }

    std::cout << "File input1.txt found." << std::endl;

    std::ofstream output("output1.txt");

    if (!output.is_open())
    {
        std::cout << "Error: cannot create output1.txt." << std::endl;
        return;
    }

    int k;
    input >> k;

    for (int i = 0; i < k; ++i)
    {
        double x1, y1;
        double x2, y2;
        double x3, y3;

        input >> x1 >> y1;
        input >> x2 >> y2;
        input >> x3 >> y3;

        Point a(x1, y1);
        Point b(x2, y2);
        Point c(x3, y3);

        char result = Geometry::whichPointIsBetween(a, b, c);

        output << result << std::endl;
    }

    std::cout << "Results have been written to output1.txt." << std::endl;
}