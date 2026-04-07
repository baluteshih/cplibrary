#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_E"
#define ERROR 0.000001
#include "default_code.hpp"

#include "Geometry/circle.hpp"

using cir = Circle<int>;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cir a, b;
    cin >> a.o >> a.r >> b.o >> b.r;
    auto res = circleIntersection(a, b);
    assert(!res.empty());
    if (res[0] > res[1]) swap(res[0], res[1]);
    cout << fixed << setprecision(8) << res[0] << " " << res[1] << "\n";
}

