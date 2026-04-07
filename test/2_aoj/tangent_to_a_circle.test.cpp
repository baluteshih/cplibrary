#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_F"
#define ERROR 0.00001
#include "default_code.hpp"

#include "Geometry/circle.hpp"

using cir = Circle<int>;
using Point = Pt<int>;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    Point p;
    cir c;
    cin >> p >> c.o >> c.r;
    auto res = pointCircleTangent(p, c);
    assert(!res.empty());
    if (res[0] > res[1]) swap(res[0], res[1]);
    cout << fixed << setprecision(10) << res[0] << "\n" << res[1] << "\n";
}

