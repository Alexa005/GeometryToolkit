
#include "PointCounting.h"

#include <algorithm>
#include <cstddef>
#include <utility>
#include <vector>

namespace
{
    // Дерево Фенвика для подсчёта точек по сжатым координатам Y.
    class FenwickTree
    {
    public:
        explicit FenwickTree(std::size_t size)
            : tree(size + 1, 0)
        {
        }

        // Добавить delta к элементу с индексом index (нумерация с нуля).
        void add(std::size_t index, int delta)
        {
            ++index;

            while (index < tree.size())
            {
                tree[index] += delta;
                index += index & (~index + 1);
            }
        }

        // Сумма первых count элементов.
        int prefixSum(std::size_t count) const
        {
            int result = 0;

            while (count > 0)
            {
                result += tree[count];
                count &= count - 1;
            }

            return result;
        }

        // Сумма элементов на полуинтервале [left, right).
        int rangeSum(std::size_t left, std::size_t right) const
        {
            return prefixSum(right) - prefixSum(left);
        }

    private:
        std::vector<int> tree;
    };

    struct Event
    {
        double x;
        double minY;
        double maxY;
        int queryIndex;
        int sign;
    };
}

PointCounting::PointCounting(const std::vector<Point>& points)
    : points(points)
{
}

std::vector<int> PointCounting::countRectangles(
    const std::vector<Rectangle>& rectangles) const
{
    const std::size_t queryCount = rectangles.size();

    std::vector<int> answers(queryCount, 0);

    if (points.empty() || rectangles.empty())
    {
        return answers;
    }

    // Сжатие координат Y всех точек.
    std::vector<double> ys;
    ys.reserve(points.size());

    for (const Point& point : points)
    {
        ys.push_back(point.y);
    }

    std::sort(ys.begin(), ys.end());

    ys.erase(
        std::unique(ys.begin(), ys.end()),
        ys.end()
    );

    // Сортируем точки слева направо.
    std::vector<Point> sortedPoints = points;

    std::sort(
        sortedPoints.begin(),
        sortedPoints.end(),
        [](const Point& a, const Point& b)
        {
            if (a.x != b.x)
            {
                return a.x < b.x;
            }

            return a.y < b.y;
        }
    );

    // Каждому прямоугольнику соответствуют два события:
    // x = minX со знаком -1 (строго левее minX);
    // x = maxX со знаком +1 (не правее maxX).
    std::vector<Event> events;
    events.reserve(queryCount * 2);

    for (std::size_t i = 0; i < queryCount; ++i)
    {
        const Rectangle& rectangle = rectangles[i];

        if (!rectangle.isValid())
        {
            continue;
        }

        events.push_back({
            rectangle.minX,
            rectangle.minY,
            rectangle.maxY,
            static_cast<int>(i),
            -1
            });

        events.push_back({
            rectangle.maxX,
            rectangle.minY,
            rectangle.maxY,
            static_cast<int>(i),
            +1
            });
    }

    // При одинаковом X сначала обрабатываем левую границу
    // (точки с таким X ещё не добавлены), затем правую.
    std::sort(
        events.begin(),
        events.end(),
        [](const Event& a, const Event& b)
        {
            if (a.x != b.x)
            {
                return a.x < b.x;
            }

            return a.sign < b.sign;
        }
    );

    FenwickTree fenwick(ys.size());

    std::size_t pointIndex = 0;

    for (const Event& event : events)
    {
        // Для левой границы нужны точки с x < event.x.
        // Для правой — точки с x <= event.x.
        while (pointIndex < sortedPoints.size() &&
            (sortedPoints[pointIndex].x < event.x ||
                (event.sign == +1 &&
                    sortedPoints[pointIndex].x == event.x)))
        {
            const Point& point = sortedPoints[pointIndex];

            const std::size_t yIndex =
                static_cast<std::size_t>(
                    std::lower_bound(
                        ys.begin(),
                        ys.end(),
                        point.y
                    ) - ys.begin()
                    );

            fenwick.add(yIndex, 1);
            ++pointIndex;
        }

        // Находим индексы координат:
        // firstY — число координат меньше minY;
        // lastY — число координат не больше maxY.
        const std::size_t firstY =
            static_cast<std::size_t>(
                std::lower_bound(
                    ys.begin(),
                    ys.end(),
                    event.minY
                ) - ys.begin()
                );

        const std::size_t lastY =
            static_cast<std::size_t>(
                std::upper_bound(
                    ys.begin(),
                    ys.end(),
                    event.maxY
                ) - ys.begin()
                );

        const int count = fenwick.rangeSum(firstY, lastY);

        answers[event.queryIndex] += event.sign * count;
    }

    return answers;
}
