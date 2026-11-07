#define PROBLEM "polygon-containment"
#include "assumption.hpp"

#include "Geometry/polygon.hpp"

using Point = Pt<long long>;
using Poly = Polygon<long long>;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    Poly poly(n);
    for (auto &p : poly)
        std::cin >> p;
    while (q--) {
        Point p;
        std::cin >> p;
        if (pointStrictlyInPoly(p, poly)) std::cout << "IN\n";
        else if (pointInPoly(p, poly)) std::cout << "ON\n";
        else std::cout << "OUT\n";
    }
}
