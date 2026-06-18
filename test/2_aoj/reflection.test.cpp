#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_B"
#define ERROR 0.00000001
#include "assumption.hpp"

#include "Geometry/line.hpp"

using Point = Pt<int>;
using Line = Ln<int>;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    Line base;
    std::cin >> base[0] >> base[1];
    int q;
    std::cin >> q;
    std::cout << std::fixed << std::setprecision(10);
    while (q--) {
        Point p;
        std::cin >> p;
        std::cout << reflection<long double>(p, base) << "\n";
    }
}
