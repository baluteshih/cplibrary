#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_I"
#define ERROR 0.000001
#include "assumption.hpp"

#include "Geometry/circle.hpp"

using cir = Circle<int>;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    cir a, b;
    std::cin >> a.o >> a.r >> b.o >> b.r;
    std::cout << std::fixed << std::setprecision(20) << circleIntersectionArea<long double>(a, b) << "\n";
}

