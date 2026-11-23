#pragma once

#include <memory>
#include <vector>
#include "Point.h"

class KDTree
{
public:
    KDTree();

    bool insert(const Point& point);
    bool contains(const Point& point) const;

    std::vector<Point> rangeSearch(
        const Point& bottomLeft,
        const Point& topRight
    ) const;

private:
    struct Node
    {
        Point point;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        explicit Node(const Point& point)
            : point(point)
        {
        }
    };

    std::unique_ptr<Node> root;

    bool insertNode(
        std::unique_ptr<Node>& node,
        const Point& point,
        int depth
    );

    bool containsNode(
        const Node* node,
        const Point& point,
        int depth
    ) const;

    void rangeSearchNode(
        const Node* node,
        const Point& bottomLeft,
        const Point& topRight,
        int depth,
        std::vector<Point>& result
    ) const;
};