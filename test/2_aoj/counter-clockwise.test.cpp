#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_C"
#include "assumption.hpp"

#include "Geometry/line.hpp"

using Point = Pt<int>;
using Line = Ln<int>;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    Point p0, p1;
    std::cin >> p0 >> p1;
    int q;
    std::cin >> q;
    while (q--) {
        Point p2;
        std::cin >> p2;
        int res = side(p0, p1, p2);
        if (res == 1) std::cout << "COUNTER_CLOCKWISE\n";
        else if (res == -1) std::cout << "CLOCKWISE\n";
        else {
            if (pointOnSeg(p2, Line(p0, p1))) std::cout << "ON_SEGMENT\n";
            else if (pointOnSeg(p1, Line(p0, p2))) std::cout << "ONLINE_FRONT\n";
            else std::cout << "ONLINE_BACK\n";
        }
    }
}
