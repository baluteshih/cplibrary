#include "testlib.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

using Point = std::pair<int, int>;

int main(int argc, char **argv) {
    registerGen(argc, argv, 1);
    std::string mode = opt<std::string>(1);
    int n = opt<int>(2);
    std::vector<Point> points;
    if (mode == "convex") {
        std::vector<Point> directions;
        for (int x = -300; x <= 300; ++x) {
            for (int y = 0; y <= 300; ++y) {
                if ((y > 0 || x > 0) && std::gcd(std::abs(x), y) == 1) {
                    directions.emplace_back(x, y);
                }
            }
        }
        std::sort(directions.begin(), directions.end(), [](Point a, Point b) {
            return 1LL * a.first * b.second - 1LL * a.second * b.first > 0;
        });
        directions.resize(static_cast<std::size_t>(n / 2));
        int x = 0, y = 0;
        for (int sign : {1, -1}) {
            for (auto [dx, dy] : directions) {
                points.emplace_back(x, y);
                x += sign * dx;
                y += sign * dy;
            }
        }
    }
    else {
        for (int i = 0; i < n; ++i) {
            int x = 0, y = 0;
            if (mode == "line") {
                x = i - n / 2;
                y = -3 * x + 17;
            }
            else if (mode == "vertical") {
                x = -100'000'000;
                y = i - n / 2;
            }
            else if (mode == "equal") {
                x = 100'000'000;
                y = -100'000'000;
            }
            else if (mode == "rectangle") {
                int t = i / 4;
                int length = n / 4;
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
                int bound = mode == "small" ? 8 : mode == "duplicates" ? 30 : 99'999'999;
                x = rnd.next(-bound, bound);
                y = rnd.next(-bound, bound);
            }
            points.emplace_back(x, y);
        }
    }
    if (mode == "sorted") {
        std::sort(points.begin(), points.end());
    }
    else if (mode == "reversed") {
        std::sort(points.rbegin(), points.rend());
    }
    else {
        shuffle(points.begin(), points.end());
    }
    std::cout << points.size() << '\n';
    for (auto [x, y] : points) {
        std::cout << x << ' ' << y << '\n';
    }
}
