#define PROBLEM "convex-hulls"
#include "assumption.hpp"

#include "Geometry/convex.hpp"

using Point = Pt<long long>;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n;
    std::cin >> n;
    std::vector<Point> vec(n);
    for (auto &p : vec)
        std::cin >> p;
    auto H = convexHull(vec);
    auto B = convexHullNonstrict(vec);
    auto [L, U] = convexHullParts(vec);
    auto output = [&](auto &arr) {
        std::cout << arr.size() << "\n";
        for (auto &p : arr)
            std::cout << p << "\n";
    };
    output(H);
    output(B);
    output(L);
    output(U);
}
