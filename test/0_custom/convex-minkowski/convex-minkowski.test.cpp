#define PROBLEM "convex-minkowski"
#include "assumption.hpp"

#include "Geometry/convex.hpp"

using Poly = Polygon<long long>;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    Poly A(n), B(m);
    for (auto &p : A)
        std::cin >> p;
    for (auto &p : B)
        std::cin >> p;
    auto res = convexMinkowski(A, B);
    std::cout << res.size() << "\n";
    for (auto &p : res)
        std::cout << p << "\n";
}
