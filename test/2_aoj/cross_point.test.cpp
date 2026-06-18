#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_C"
#include "assumption.hpp"

#include "Geometry/line.hpp"

using Point = Pt<int>;
using Line = Ln<int>;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int q;
    std::cin >> q;
    std::cout << std::fixed << std::setprecision(10);
    while (q--) {
        Line l1, l2;
        std::cin >> l1[0] >> l1[1] >> l2[0] >> l2[1];
        std::cout << lineIntersection(l1, l2) << "\n";
    }
}
