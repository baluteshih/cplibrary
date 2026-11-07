#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>

struct Point {
    long long x, y;
    Point operator-(Point other) const {
        return {x - other.x, y - other.y};
    }
    bool operator==(const Point &) const = default;
};

long long cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

long long turn(Point a, Point b, Point c) {
    return cross(b - a, c - a);
}

bool onSegment(Point p, Point a, Point b) {
    return turn(a, b, p) == 0 && std::min(a.x, b.x) <= p.x && p.x <= std::max(a.x, b.x) && std::min(a.y, b.y) <= p.y && p.y <= std::max(a.y, b.y);
}

int location(const std::vector<Point> &polygon, Point point) {
    int n = static_cast<int>(polygon.size());
    if (n == 1) {
        return point == polygon[0] ? 0 : -1;
    }
    if (n == 2) {
        return onSegment(point, polygon[0], polygon[1]) ? 0 : -1;
    }
    long long first = turn(polygon[0], polygon[1], point);
    long long last = turn(polygon[0], polygon[n - 1], point);
    if (first < 0 || last > 0) {
        return -1;
    }
    if (first == 0) {
        return onSegment(point, polygon[0], polygon[1]) ? 0 : -1;
    }
    if (last == 0) {
        return onSegment(point, polygon[0], polygon[n - 1]) ? 0 : -1;
    }
    int left = 1, right = n - 1;
    while (right - left > 1) {
        int middle = (left + right) / 2;
        if (turn(polygon[0], polygon[middle], point) >= 0) {
            left = middle;
        }
        else {
            right = middle;
        }
    }
    long long value = turn(polygon[left], polygon[right], point);
    return (value > 0) - (value < 0);
}

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, 200'000, "n");
    inf.readSpace();
    int q = inf.readInt(1, 200'000, "q");
    inf.readEoln();
    std::vector<Point> polygon;
    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(-100'000'000, 100'000'000, "x");
        inf.readSpace();
        int y = inf.readInt(-100'000'000, 100'000'000, "y");
        inf.readEoln();
        polygon.push_back({x, y});
    }
    auto less = [](Point a, Point b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    };
    auto sorted = polygon;
    std::sort(sorted.begin(), sorted.end(), less);
    ensuref(std::adjacent_find(sorted.begin(), sorted.end()) == sorted.end(), "duplicate vertex");
    if (n <= 2) {
        ensuref(polygon == sorted, "segment endpoints must be lexicographically ordered");
    }
    else {
        std::vector<Point> hull;
        for (Point p : sorted) {
            while (hull.size() >= 2 && turn(hull[hull.size() - 2], hull.back(), p) <= 0) {
                hull.pop_back();
            }
            hull.push_back(p);
        }
        std::size_t lowerSize = hull.size();
        for (int i = n - 2; i >= 0; --i) {
            Point p = sorted[static_cast<std::size_t>(i)];
            while (hull.size() > lowerSize && turn(hull[hull.size() - 2], hull.back(), p) <= 0) {
                hull.pop_back();
            }
            hull.push_back(p);
        }
        hull.pop_back();
        ensuref(hull.size() == polygon.size(), "polygon must be nondegenerate and strictly convex");
        int start = static_cast<int>(std::min_element(polygon.begin(), polygon.end(), less) - polygon.begin());
        for (int i = 0; i < n; ++i) {
            ensuref(polygon[(start + i) % n] == hull[static_cast<std::size_t>(i)], "polygon must traverse its hull once counterclockwise");
        }
    }
    for (int i = 0; i < q; ++i) {
        std::string type = inf.readToken("[IDT]", "type");
        inf.readSpace();
        int x = inf.readInt(-100'000'000, 100'000'000, "x");
        inf.readSpace();
        int y = inf.readInt(-100'000'000, 100'000'000, "y");
        inf.readEoln();
        if (type == "D") {
            ensuref(x != 0 || y != 0, "zero direction");
        }
        if (type == "T") {
            ensuref(n >= 3, "tangent queries require n >= 3");
            ensuref(location(polygon, {x, y}) == -1, "tangent query point must be strictly outside");
        }
    }
    inf.readEof();
    return 42;
}
