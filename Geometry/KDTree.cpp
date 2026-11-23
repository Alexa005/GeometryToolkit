#include "KDTree.h"

#include <algorithm>

KDTree::KDTree() = default;

bool KDTree::insert(const Point& point)
{
    return insertNode(root, point, 0);
}

bool KDTree::insertNode(
    std::unique_ptr<Node>& node,
    const Point& point,
    int depth
)
{
    if (!node)
    {
        node = std::make_unique<Node>(point);
        return true;
    }

    if (node->point.x == point.x &&
        node->point.y == point.y)
    {
        return false;
    }

    // Четные уровни сравнивают x, нечетные — y.
    const bool compareX = (depth % 2 == 0);

    bool goLeft;

    if (compareX)
        goLeft = point.x < node->point.x;
    else
        goLeft = point.y < node->point.y;

    if (goLeft)
        return insertNode(node->left, point, depth + 1);

    return insertNode(node->right, point, depth + 1);
}

bool KDTree::contains(const Point& point) const
{
    return containsNode(root.get(), point, 0);
}

bool KDTree::containsNode(
    const Node* node,
    const Point& point,
    int depth
) const
{
    if (node == nullptr)
        return false;

    if (node->point.x == point.x &&
        node->point.y == point.y)
    {
        return true;
    }

    const bool compareX = (depth % 2 == 0);

    bool goLeft;

    if (compareX)
        goLeft = point.x < node->point.x;
    else
        goLeft = point.y < node->point.y;

    if (goLeft)
        return containsNode(node->left.get(), point, depth + 1);

    return containsNode(node->right.get(), point, depth + 1);
}

std::vector<Point> KDTree::rangeSearch(
    const Point& bottomLeft,
    const Point& topRight
) const
{
    std::vector<Point> result;

    if (bottomLeft.x > topRight.x ||
        bottomLeft.y > topRight.y)
    {
        return result;
    }

    rangeSearchNode(
        root.get(),
        bottomLeft,
        topRight,
        0,
        result
    );

    return result;
}

void KDTree::rangeSearchNode(
    const Node* node,
    const Point& bottomLeft,
    const Point& topRight,
    int depth,
    std::vector<Point>& result
) const
{
    if (node == nullptr)
        return;

    const Point& p = node->point;

    // Проверяем, входит ли точка в прямоугольник.
    if (p.x >= bottomLeft.x &&
        p.x <= topRight.x &&
        p.y >= bottomLeft.y &&
        p.y <= topRight.y)
    {
        result.push_back(p);
    }

    const bool compareX = (depth % 2 == 0);

    if (compareX)
    {
        if (bottomLeft.x <= p.x)
        {
            rangeSearchNode(
                node->left.get(),
                bottomLeft,
                topRight,
                depth + 1,
                result
            );
        }

        if (topRight.x >= p.x)
        {
            rangeSearchNode(
                node->right.get(),
                bottomLeft,
                topRight,
                depth + 1,
                result
            );
        }
    }
    else
    {
        if (bottomLeft.y <= p.y)
        {
            rangeSearchNode(
                node->left.get(),
                bottomLeft,
                topRight,
                depth + 1,
                result
            );
        }

        if (topRight.y >= p.y)
        {
            rangeSearchNode(
                node->right.get(),
                bottomLeft,
                topRight,
                depth + 1,
                result
            );
        }
    }
}