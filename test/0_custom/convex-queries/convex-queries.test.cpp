#define PROBLEM "convex-queries"
#include "assumption.hpp"

#include "Geometry/convex.hpp"

using Point = Pt<long long>;
using Poly = Polygon<long long>;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    Poly convex(n);
    for (auto &p : convex)
        std::cin >> p;
    while (q--) {
        char c;
        Point p;
        std::cin >> c >> p;
        if (c == 'I') {
            int res = pointInConvex(p, convex);
            if (res == 1) std::cout << "IN\n";
            else if (res == 0) std::cout << "ON\n";
            else std::cout << "OUT\n";
        }
        else if (c == 'D') {
            int res = tangentDirection(p, convex);
            std::cout << res << "\n";
        }
        else {
            auto [l, r] = tangentLineToConvex(p, convex);
            std::cout << l << " " << r << "\n";
        }
    }
}
