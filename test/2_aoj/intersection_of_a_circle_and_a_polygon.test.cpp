#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_H"
#define ERROR 0.00001
#include "default_code.hpp"

#include "Geometry/circle.hpp"

using cir = Circle<int>;
using polygon = Polygon<int>;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cir c;
    int n;
    cin >> n >> c.r;
    polygon poly(n);
    for (auto &p : poly)
        cin >> p;
    cout << fixed << setprecision(10) << polyCircleIntersectionArea(poly, c) << "\n";
}

