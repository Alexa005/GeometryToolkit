
#include <iostream>
#include <limits>
#include <string>
#include <vector>

// ==================== TASK DECLARATIONS ====================

// Basic geometry
void runCollinearityCheck();
void runOrientationCheck();
void runThreePointPositionCheck();
void runLineIntersection();

// Segment operations
void runSegmentIntersectionCheck();
void runAllSegmentIntersections();
void runSegmentIntersectionPoint();

// Polygon operations
void runQuadrilateralConvexityCheck();
void runPolygonIntersectionCheck();
void runPolygonSimplicityCheck();
void runPolygonIntersection();
void runPointInAngleCheck();
void runPointInPolygonCheck();

// Geometric search
void runRectanglePointCounting();
void runPointLocation();
void runKDTreeSearch();


// ==================== MENU STRUCTURES ====================

struct Task
{
    std::string name;
    void (*function)();
};

struct Menu
{
    std::string title;
    std::vector<Task> tasks;
};


// ==================== INPUT ====================

int readChoice()
{
    int choice;

    if (std::cin >> choice)
    {
        return choice;
    }

    if (std::cin.eof())
    {
        return 0;
    }

    std::cin.clear();
    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(),
        '\n'
    );

    return -1;
}


// ==================== MENU DISPLAY ====================

void printMainMenu()
{
    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "           GEOMETRY TOOLKIT\n";
    std::cout << "========================================\n";

    std::cout << "1. Basic geometry\n";
    std::cout << "2. Segment operations\n";
    std::cout << "3. Polygon operations\n";
    std::cout << "4. Geometric search\n";

    std::cout << "0. Exit\n";

    std::cout << "========================================\n";
    std::cout << "Choose category: ";
}


void printTaskMenu(const Menu& menu)
{
    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "  " << menu.title << "\n";
    std::cout << "========================================\n";

    for (std::size_t i = 0; i < menu.tasks.size(); ++i)
    {
        std::cout << i + 1 << ". "
            << menu.tasks[i].name
            << "\n";
    }

    std::cout << "0. Back to main menu\n";

    std::cout << "========================================\n";
    std::cout << "Choose task: ";
}


// ==================== MENU EXECUTION ====================

void runMenu(const Menu& menu)
{
    while (true)
    {
        printTaskMenu(menu);

        const int choice = readChoice();

        if (choice == 0)
        {
            return;
        }

        if (choice < 1 ||
            choice > static_cast<int>(menu.tasks.size()))
        {
            std::cout << "Invalid option. Try again.\n";
            continue;
        }

        const Task& task = menu.tasks[choice - 1];

        std::cout << "\n";
        std::cout << "----------------------------------------\n";
        std::cout << task.name << "\n";
        std::cout << "----------------------------------------\n";

        task.function();

        std::cout << "\nTask completed.\n";
    }
}


// ==================== MENUS ====================

const Menu basicGeometryMenu =
{
    "BASIC GEOMETRY",
    {
        {"Check collinearity of three points", runCollinearityCheck},
        {"Determine orientation of three points", runOrientationCheck},
        {"Determine the position of three points", runThreePointPositionCheck},
        {"Find intersection of two lines", runLineIntersection}
    }
};


const Menu segmentOperationsMenu =
{
    "SEGMENT OPERATIONS",
    {
        {"Check intersection of two segments", runSegmentIntersectionCheck},
        {"Find all pairwise segment intersections", runAllSegmentIntersections},
        {"Find intersection point of two segments", runSegmentIntersectionPoint}
    }
};


const Menu polygonOperationsMenu =
{
    "POLYGON OPERATIONS",
    {
        {"Check whether a quadrilateral is convex", runQuadrilateralConvexityCheck},
        {"Check intersection of two simple polygons", runPolygonIntersectionCheck},
        {"Test polygon simplicity", runPolygonSimplicityCheck},
        {"Polygon intersection", runPolygonIntersection},
        {"Check whether a point lies inside an angle", runPointInAngleCheck},
        {"Check whether a point lies inside a polygon", runPointInPolygonCheck}
    }
};


const Menu geometricSearchMenu =
{
    "GEOMETRIC SEARCH",
    {
        {"Count points inside rectangles", runRectanglePointCounting},
        {"Locate a point in a planar subdivision", runPointLocation},
        {"Search using a 2D k-D tree", runKDTreeSearch}
    }
};


// ==================== MAIN ====================

int main()
{
    system("cls 1251");
    while (true)
    {
        printMainMenu();

        const int choice = readChoice();

        switch (choice)
        {
        case 1:
            runMenu(basicGeometryMenu);
            break;

        case 2:
            runMenu(segmentOperationsMenu);
            break;

        case 3:
            runMenu(polygonOperationsMenu);
            break;

        case 4:
            runMenu(geometricSearchMenu);
            break;

        case 0:
            std::cout << "\nThank you for using Geometry Toolkit!\n";
            return 0;

        default:
            std::cout << "Invalid option. Try again.\n";
            break;
        }
    }
}
