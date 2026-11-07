#define PROBLEM "convex-line-intersection"
#include "assumption.hpp"

#include "Geometry/convex.hpp"

using Point = Pt<long long>;
using Line = Ln<long long>;
using Poly = Polygon<long long>;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    Poly convex(n);
    for (auto &p : convex)
        std::cin >> p;
    while (q--) {
        Line ln;
        std::cin >> ln;
        auto [l, r] = lineIntersectConvex(ln, convex);
        if (l == -1) std::cout << "EMPTY\n";
        else if (r == -1) std::cout << "POINT " << l << "\n";
        else if (l == r) std::cout << "EDGE " << l << "\n";
        else std::cout << "CUT " << l << " " << r << "\n";
    }
}
