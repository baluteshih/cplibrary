#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>

using Point = std::pair<long long, long long>;

long long turn(Point a, Point b, Point c) {
    return (b.first - a.first) * (c.second - a.second) - (b.second - a.second) * (c.first - a.first);
}

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(3, 200'000, "n");
    inf.readSpace();
    int q = inf.readInt(1, 200'000, "q");
    inf.readEoln();
    std::vector<Point> polygon;
    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(-100'000'000, 100'000'000, "x");
        inf.readSpace();
        int y = inf.readInt(-100'000'000, 100'000'000, "y");
        inf.readEoln();
        polygon.emplace_back(x, y);
    }
    auto sorted = polygon;
    std::sort(sorted.begin(), sorted.end());
    ensuref(std::adjacent_find(sorted.begin(), sorted.end()) == sorted.end(), "duplicate polygon vertex");
    std::vector<Point> hull;
    for (Point point : sorted) {
        while (hull.size() >= 2 && turn(hull[hull.size() - 2], hull.back(), point) <= 0) {
            hull.pop_back();
        }
        hull.push_back(point);
    }
    std::size_t lowerSize = hull.size();
    for (int i = n - 2; i >= 0; --i) {
        Point point = sorted[static_cast<std::size_t>(i)];
        while (hull.size() > lowerSize && turn(hull[hull.size() - 2], hull.back(), point) <= 0) {
            hull.pop_back();
        }
        hull.push_back(point);
    }
    hull.pop_back();
    ensuref(hull.size() == polygon.size(), "polygon must be nondegenerate and strictly convex");
    int start = static_cast<int>(std::min_element(polygon.begin(), polygon.end()) - polygon.begin());
    for (int i = 0; i < n; ++i) {
        ensuref(polygon[(start + i) % n] == hull[static_cast<std::size_t>(i)], "vertices must traverse the convex hull exactly once counterclockwise");
    }
    for (int i = 0; i < q; ++i) {
        int ax = inf.readInt(-100'000'000, 100'000'000, "ax");
        inf.readSpace();
        int ay = inf.readInt(-100'000'000, 100'000'000, "ay");
        inf.readSpace();
        int bx = inf.readInt(-100'000'000, 100'000'000, "bx");
        inf.readSpace();
        int by = inf.readInt(-100'000'000, 100'000'000, "by");
        inf.readEoln();
        ensuref(ax != bx || ay != by, "query endpoints must differ");
    }
    inf.readEof();
    return 42;
}
