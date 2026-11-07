#include "testlib.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

using Point = std::pair<long long, long long>;

long long turn(Point a, Point b, Point c) {
    return (b.first - a.first) * (c.second - a.second) - (b.second - a.second) * (c.first - a.first);
}

std::vector<Point> hull(std::vector<Point> points) {
    std::sort(points.begin(), points.end());
    points.erase(std::unique(points.begin(), points.end()), points.end());
    std::vector<Point> result;
    for (Point point : points) {
        while (result.size() >= 2 && turn(result[result.size() - 2], result.back(), point) <= 0) {
            result.pop_back();
        }
        result.push_back(point);
    }
    std::size_t lowerSize = result.size();
    for (int i = static_cast<int>(points.size()) - 2; i >= 0; --i) {
        Point point = points[static_cast<std::size_t>(i)];
        while (result.size() > lowerSize && turn(result[result.size() - 2], result.back(), point) <= 0) {
            result.pop_back();
        }
        result.push_back(point);
    }
    result.pop_back();
    return result;
}

bool legal(Point point) {
    return std::abs(point.first) <= 100'000'000 && std::abs(point.second) <= 100'000'000;
}

int main(int argc, char **argv) {
    registerGen(argc, argv, 1);
    std::string shape = opt<std::string>(1);
    int requested = opt<int>(2), q = opt<int>(3);
    std::string mode = opt<std::string>(4);
    std::vector<Point> polygon;
    if (shape == "convex") {
        std::vector<Point> directions;
        for (int x = -300; x <= 300; ++x) {
            for (int y = 0; y <= 300; ++y) {
                if ((y > 0 || x > 0) && std::gcd(std::abs(x), y) == 1) {
                    directions.emplace_back(x, y);
                }
            }
        }
        std::sort(directions.begin(), directions.end(), [](Point a, Point b) {
            return a.first * b.second - a.second * b.first > 0;
        });
        directions.resize(static_cast<std::size_t>(requested / 2));
        long long x = -10'000'000, y = -10'000'000;
        for (int sign : {1, -1}) {
            for (auto [dx, dy] : directions) {
                polygon.emplace_back(x, y);
                x += sign * dx;
                y += sign * dy;
            }
        }
    }
    else if (shape == "parabola") {
        for (int i = 0; i < requested; ++i) {
            long long x = i - requested / 2;
            polygon.emplace_back(x, x * x);
        }
    }
    else if (shape == "square") {
        polygon = {{-50'000'000, -50'000'000}, {50'000'000, -50'000'000}, {50'000'000, 50'000'000}, {-50'000'000, 50'000'000}};
    }
    else {
        int bound = shape == "small" ? 20 : 90'000'000;
        for (int i = 0; i < requested; ++i) {
            int x = rnd.next(-bound, bound);
            int y = rnd.next(-bound, bound);
            polygon.emplace_back(x, y);
        }
    }
    polygon = hull(polygon);
    int n = static_cast<int>(polygon.size());
    ensuref(n >= 3, "need a nondegenerate polygon");
    int shift = rnd.next(n);
    std::rotate(polygon.begin(), polygon.begin() + shift, polygon.end());
    std::cout << n << ' ' << q << '\n';
    for (auto [x, y] : polygon) {
        std::cout << x << ' ' << y << '\n';
    }
    Point previousA = polygon[0], previousB = polygon[1];
    for (int i = 0; i < q; ++i) {
        int vertex = rnd.next(n);
        Point a = polygon[vertex], b = polygon[(vertex + 1) % n];
        int kind = mode == "edge" ? 0 : mode == "vertex" ? 1 : mode == "outside" ? 4 : mode == "random" ? 6 : i % 10;
        if (kind == 1) {
            int offset = rnd.next(1, n - 1);
            b = polygon[(vertex + offset) % n];
        }
        else if (kind == 2) {
            Point next = polygon[(vertex + 1) % n], previous = polygon[(vertex + n - 1) % n];
            b = {a.first + next.first - previous.first, a.second + next.second - previous.second};
        }
        else if (kind == 3) {
            Point p = polygon[0], r = polygon[n / 3], s = polygon[2 * n / 3];
            a = {(p.first + r.first + s.first) / 3, (p.second + r.second + s.second) / 3};
            b = {a.first + 1, a.second};
        }
        else if (kind == 4) {
            a = {-100'000'000, -100'000'000};
            b = {-100'000'000, 100'000'000};
        }
        else if (kind == 5) {
            a.second += 1;
            b.second += 1;
        }
        else if (kind == 6 || kind == 9) {
            a.first = rnd.next(-100'000'000, 100'000'000);
            a.second = rnd.next(-100'000'000, 100'000'000);
            b.first = rnd.next(-100'000'000, 100'000'000);
            b.second = rnd.next(-100'000'000, 100'000'000);
        }
        else if (kind == 7) {
            a = previousB;
            b = previousA;
        }
        else if (kind == 8) {
            b.first = rnd.next(-100'000'000, 100'000'000);
            b.second = rnd.next(-100'000'000, 100'000'000);
        }
        if (!legal(a) || !legal(b) || a == b) {
            a = polygon[vertex];
            b = polygon[(vertex + 1) % n];
        }
        std::cout << a.first << ' ' << a.second << ' ' << b.first << ' ' << b.second << '\n';
        previousA = a;
        previousB = b;
    }
}
