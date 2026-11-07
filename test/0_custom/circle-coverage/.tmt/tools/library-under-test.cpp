#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numbers>
#include <numeric>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>
#include "Geometry/circle_cover.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<Circle<int>> circles(static_cast<std::size_t>(n));
    for (auto &circle : circles) {
        std::cin >> circle.o >> circle.r;
    }
    auto area = circle_cover(circles);
    std::cout << std::fixed << std::setprecision(15);
    for (int k = 1; k <= n; ++k) {
        std::cout << area[k] << '\n';
    }
}
