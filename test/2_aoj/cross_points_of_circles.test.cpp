#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_E"
#define ERROR 0.000001
#include "assumption.hpp"

#include "Geometry/circle.hpp"

using cir = Circle<int>;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    cir a, b;
    std::cin >> a.o >> a.r >> b.o >> b.r;
    auto res = circleIntersection(a, b);
    assert(!res.empty());
    if (res[0] > res[1]) std::swap(res[0], res[1]);
    std::cout << std::fixed << std::setprecision(8) << res[0] << " " << res[1] << "\n";
}

