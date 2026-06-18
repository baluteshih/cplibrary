#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_C"
#define ERROR 0.00001
#include "assumption.hpp"

#include "Geometry/convex.hpp"

using Point = Pt<int>;
using Line = Ln<int>;
using polygon = Polygon<int>;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n;
    std::cin >> n;
    polygon poly(n);
    for (auto &p : poly)
        std::cin >> p;
    poly = convexHull(poly);
    int q;
    std::cin >> q;
    std::cout << std::fixed << std::setprecision(8);
    while (q--) {
        Line ln;
        std::cin >> ln;
        auto [l, r] = lineIntersectConvex(ln, poly);
        if (r == -1 || l == r) {
            if (side(ln[0], ln[1], poly[0]) > 0 || side(ln[0], ln[1], poly[1]) > 0 || side(ln[0], ln[1], poly[2]) > 0) std::cout << (double)poly.area() / 2 << "\n";
            else std::cout << (double)0 << "\n";
        }
        else {
            Polygon<double> res;
            res.push_back(lineIntersection(ln, Line(poly[r], poly.at(r + 1))));
            for (int i = r + 1; i % int(poly.size()) != l; ++i)
                res.push_back(poly.at(i));
            res.push_back(poly[l]);
            res.push_back(lineIntersection(ln, Line(poly[l], poly.at(l + 1))));
            std::cout << res.area() / 2 << "\n";
        }
    }
}
