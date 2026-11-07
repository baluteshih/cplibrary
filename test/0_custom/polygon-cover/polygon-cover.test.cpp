#define PROBLEM "polygon-union"
#include "assumption.hpp"

#include "Geometry/polygon.hpp"

using Point = Pt<long long>;
using Poly = Polygon<long long>;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int k;
    std::cin >> k;
    std::vector<Poly> vec(k);
    for (auto &v : vec) {
        int n;
        std::cin >> n;
        v.resize(n);
        for (auto &p : v)
            std::cin >> p;
    }
    auto res = polyCoverArea(vec);
    std::cout << std::fixed << std::setprecision(12);
    for (int i = 1; i <= k; ++i)
        std::cout << res[i] << " \n"[i == k];
}
