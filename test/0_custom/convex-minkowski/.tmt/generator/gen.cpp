#include "testlib.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

using Point = std::pair<long long, long long>;
using Cloud = std::vector<Point>;

Cloud makeCloud(const std::string &mode, int n, int variant) {
    Cloud points;
    if (mode == "convex" || mode == "parallel") {
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
        directions.resize(static_cast<std::size_t>(n / 2));
        long long x = 0, y = 0;
        for (int sign : {1, -1}) {
            for (auto [dx, dy] : directions) {
                points.emplace_back(x + 60'000'000, y - 60'000'000);
                x += sign * dx;
                y += sign * dy;
            }
        }
        if (mode == "convex" && variant == 1) {
            for (auto &point : points) {
                long long originalX = point.first - 60'000'000, originalY = point.second + 60'000'000;
                point = {originalX - originalY - 50'000'000, originalX + originalY + 50'000'000};
            }
        }
    }
    else {
        for (int i = 0; i < n; ++i) {
            long long x = 0, y = 0;
            if (mode == "equal") {
                x = 100'000'000;
                y = -100'000'000;
            }
            else if (mode == "line" || mode == "crossing-lines") {
                x = i - n / 2;
                y = (mode == "crossing-lines" && variant == 1) ? -2 * x : 3 * x;
            }
            else if (mode == "rectangle") {
                int t = i / 4;
                int length = std::max(1, n / 4);
                switch (i % 4) {
                    case 0: x = t; y = 0; break;
                    case 1: x = length; y = t; break;
                    case 2: x = length - t; y = length; break;
                    default: x = 0; y = length - t; break;
                }
            }
            else if (mode == "interior" && i < 4) {
                x = i & 1 ? 100'000'000 : -100'000'000;
                y = i & 2 ? 100'000'000 : -100'000'000;
            }
            else {
                int bound = mode == "small" ? 10 : mode == "duplicates" ? 20 : 99'999'999;
                x = rnd.next(-bound, bound);
                y = rnd.next(-bound, bound);
            }
            points.emplace_back(x, y);
        }
    }
    shuffle(points.begin(), points.end());
    return points;
}

int main(int argc, char **argv) {
    registerGen(argc, argv, 1);
    std::string mode = opt<std::string>(1);
    int n = opt<int>(2), m = opt<int>(3);
    Cloud a = makeCloud(mode, n, 0);
    Cloud b = makeCloud(mode, m, 1);
    std::cout << a.size() << ' ' << b.size() << '\n';
    for (const auto &cloud : {a, b}) {
        for (auto [x, y] : cloud) {
            std::cout << x << ' ' << y << '\n';
        }
    }
}
