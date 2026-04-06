#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_C"
#include "default_code.hpp"

#include "Geometry/Polygon.hpp"

using Point = Pt<int>;
using polygon = Polygon<int>;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    polygon poly(n);
    for (auto &p : poly)
        cin >> p;
    int q;
    cin >> q;
    while (q--) {
        Point p;
        cin >> p;
        if (pointStrictlyInPoly(p, poly)) cout << "2\n";
        else if (pointInPoly(p, poly)) cout << "1\n";
        else cout << "0\n";
    }
}
