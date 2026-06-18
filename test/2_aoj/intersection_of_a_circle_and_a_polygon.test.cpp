#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_H"
#define ERROR 0.00001
#include "assumption.hpp"

#include "Geometry/circle.hpp"

using cir = Circle<int>;
using polygon = Polygon<int>;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    cir c;
    int n;
    std::cin >> n >> c.r;
    polygon poly(n);
    for (auto &p : poly)
        std::cin >> p;
    std::cout << std::fixed << std::setprecision(10) << polyCircleIntersectionArea(poly, c) << "\n";
}

