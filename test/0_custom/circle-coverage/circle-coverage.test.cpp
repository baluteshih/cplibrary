#define PROBLEM "circle-coverage"
#include "assumption.hpp"

#include "Geometry/circle_cover.hpp"

using Cir = Circle<int>;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n;
    std::cin >> n;
    std::vector<Cir> arr(n);
    for (auto &p : arr)
        std::cin >> p.o >> p.r;
    auto res = circle_cover(arr);
    std::cout << std::fixed << std::setprecision(12);
    for (int i = 1; i <= n; ++i)
        std::cout << res[i] << "\n";
}
