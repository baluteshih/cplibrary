#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_D"
#define ERROR 0.000001
#include "assumption.hpp"

#include "Geometry/circle.hpp"

using cir = Circle<int>;
using Line = Ln<int>;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    cir a;
    std::cin >> a.o >> a.r;
    int q;
    std::cin >> q;
    std::cout << std::fixed << std::setprecision(8);
    while (q--) {
        Line ln;
        std::cin >> ln;
        auto res = circleLineIntersection(a, ln);
        assert(!res.empty());
        if (res[0] > res[1]) std::swap(res[0], res[1]);
        std::cout << res[0] << " " << res[1] << "\n";
    }
}

