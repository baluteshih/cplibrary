#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_C"
#define ERROR 0.00001
#include "default_code.hpp"

#include "Geometry/convex.hpp"

using Point = Pt<int>;
using Line = Ln<int>;
using polygon = Polygon<int>;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    polygon poly(n);
    for (auto &p : poly)
        cin >> p;
    poly = convexHull(poly);
    int q;
    cin >> q;
    cout << fixed << setprecision(8);
    while (q--) {
        Line ln;
        cin >> ln;
        auto [l, r] = lineIntersectConvex(ln, poly);
        if (r == -1 || l == r) {
            if (side(ln[0], ln[1], poly[0]) > 0 || side(ln[0], ln[1], poly[1]) > 0 || side(ln[0], ln[1], poly[2]) > 0) cout << (double)poly.area() / 2 << "\n";
            else cout << (double)0 << "\n";
        }
        else {
            Polygon<double> res;
            res.push_back(lineIntersection(ln, Line(poly[r], poly.at(r + 1))));
            for (int i = r + 1; i % SZ(poly) != l; ++i)
                res.push_back(poly.at(i));
            res.push_back(poly[l]);
            res.push_back(lineIntersection(ln, Line(poly[l], poly.at(l + 1))));
            cout << res.area() / 2 << "\n";
        }
    }
}
