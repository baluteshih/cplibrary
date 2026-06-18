#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_C"
#include "assumption.hpp"

#include "Geometry/polygon.hpp"

using Point = Pt<int>;
using polygon = Polygon<int>;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n;
    std::cin >> n;
    polygon poly(n);
    for (auto &p : poly)
        std::cin >> p;
    int q;
    std::cin >> q;
    while (q--) {
        Point p;
        std::cin >> p;
        if (pointStrictlyInPoly(p, poly)) std::cout << "2\n";
        else if (pointInPoly(p, poly)) std::cout << "1\n";
        else std::cout << "0\n";
    }
}
