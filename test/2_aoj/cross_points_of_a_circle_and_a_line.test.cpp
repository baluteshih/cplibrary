#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_D"
#define ERROR 0.000001
#include "default_code.hpp"

#include "Geometry/circle.hpp"

using cir = Circle<int>;
using Line = Ln<int>;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cir a;
    cin >> a.o >> a.r;
    int q;
    cin >> q;
    cout << fixed << setprecision(8);
    while (q--) {
        Line ln;
        cin >> ln;
        auto res = circleLineIntersection(a, ln);
        assert(!res.empty());
        if (res[0] > res[1]) swap(res[0], res[1]);
        cout << res[0] << " " << res[1] << "\n";
    }
}

