#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <numeric>
#include <ranges>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>
#include "Geometry/convex.hpp"

using Point = Pt<long long>;

void print(const auto &points) {
    std::cout << points.size() << '\n';
    for (const auto &point : points) {
        std::cout << point.x << ' ' << point.y << '\n';
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<Point> points(static_cast<std::size_t>(n));
    for (auto &point : points) {
        std::cin >> point;
    }
    auto hull = convexHull(points);
    auto boundary = convexHullNonstrict(points);
    auto [lower, upper] = convexHullParts(points);
    std::sort(points.begin(), points.end());
    points.erase(std::unique(points.begin(), points.end()), points.end());
    auto sortedHull = convexHull(points, false);
    auto sortedBoundary = convexHullNonstrict(points, false);
    auto [sortedLower, sortedUpper] = convexHullParts(points, false);
    if (hull != sortedHull || boundary != sortedBoundary || lower != sortedLower || upper != sortedUpper) {
        std::cerr << "sort_and_unique=false differs from the default path\n";
        return 1;
    }
    print(hull);
    print(boundary);
    print(lower);
    print(upper);
}
