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
    if (points.size() <= 1) {
        return points;
    }
    std::vector<Point> result;
    for (Point p : points) {
        while (result.size() >= 2 && turn(result[result.size() - 2], result.back(), p) <= 0) {
            result.pop_back();
        }
        result.push_back(p);
    }
    std::size_t lowerSize = result.size();
    for (int i = static_cast<int>(points.size()) - 2; i >= 0; --i) {
        Point p = points[static_cast<std::size_t>(i)];
        while (result.size() > lowerSize && turn(result[result.size() - 2], result.back(), p) <= 0) {
            result.pop_back();
        }
        result.push_back(p);
    }
    result.pop_back();
    return result;
}

bool legal(Point p) {
    return std::abs(p.first) <= 100'000'000 && std::abs(p.second) <= 100'000'000;
}

int main(int argc, char **argv) {
    registerGen(argc, argv, 1);
    std::string shape = opt<std::string>(1);
    int requested = opt<int>(2), q = opt<int>(3);
    std::string mode = opt<std::string>(4);
    std::vector<Point> polygon;
    if (shape == "point") {
        polygon = {{99'999'999, -99'999'999}};
    }
    else if (shape == "segment") {
        polygon = {{-80'000'000, 70'000'000}, {80'000'000, -70'000'000}};
    }
    else if (shape == "vertical") {
        polygon = {{30, -80'000'000}, {30, 80'000'000}};
    }
    else if (shape == "square") {
        polygon = {{-50'000'000, -50'000'000}, {50'000'000, -50'000'000}, {50'000'000, 50'000'000}, {-50'000'000, 50'000'000}};
    }
    else if (shape == "convex") {
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
    else {
        int bound = shape == "small" ? 20 : 70'000'000;
        for (int i = 0; i < requested; ++i) {
            int x = rnd.next(-bound, bound);
            int y = rnd.next(-bound, bound);
            polygon.emplace_back(x, y);
        }
    }
    polygon = hull(polygon);
    int n = static_cast<int>(polygon.size());
    if (n >= 3) {
        int shift = rnd.next(n);
        std::rotate(polygon.begin(), polygon.begin() + shift, polygon.end());
    }
    std::cout << n << ' ' << q << '\n';
    for (auto [x, y] : polygon) {
        std::cout << x << ' ' << y << '\n';
    }
    for (int i = 0; i < q; ++i) {
        int index = rnd.next(n);
        Point p = polygon[index], next = polygon[(index + 1) % n];
        long long dx = next.first - p.first, dy = next.second - p.second;
        long long divisor = std::gcd(std::abs(dx), std::abs(dy));
        int kind = i % 12;
        char type = mode == "I" ? 'I' : mode == "D" ? 'D' : mode == "T" && n >= 3 ? 'T' : kind % 3 == 0 ? 'I' : kind % 3 == 1 ? 'D' : n >= 3 ? 'T' : 'I';
        Point value;
        if (type == 'I') {
            if (kind < 4) {
                value = p;
            }
            else if (kind < 8 && divisor > 1) {
                value = {p.first + dx / divisor, p.second + dy / divisor};
            }
            else if (kind == 8 && n >= 3) {
                value = {(polygon[0].first + polygon[n / 3].first + polygon[2 * n / 3].first) / 3,
                         (polygon[0].second + polygon[n / 3].second + polygon[2 * n / 3].second) / 3};
            }
            else {
                value.first = rnd.next(-100'000'000, 100'000'000);
                value.second = rnd.next(-100'000'000, 100'000'000);
            }
        }
        else if (type == 'D') {
            if (kind < 6 && divisor > 0) {
                int sign = i & 1 ? 1 : -1;
                value = {sign * dx / divisor, sign * dy / divisor};
            }
            else if (kind < 9) {
                value = {-100'000'000, (i & 1) ? 1 : -1};
            }
            else {
                value.first = rnd.next(-100'000'000, 100'000'000);
                value.second = rnd.next(-100'000'000, 100'000'000);
            }
            if (value == Point(0, 0) || !legal(value)) {
                value = {1, 0};
            }
        }
        else {
            if (kind < 4) {
                value = {p.first - dx / divisor, p.second - dy / divisor};
            }
            else if (kind < 8) {
                value = {p.first + dy / divisor, p.second - dx / divisor};
            }
            else {
                value = {-100'000'000, 100'000'000};
            }
            if (!legal(value)) {
                value = {-100'000'000, 100'000'000};
            }
        }
        std::cout << type << ' ' << value.first << ' ' << value.second << '\n';
    }
}
