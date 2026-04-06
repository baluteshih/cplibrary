#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_A"
#include "default_code.hpp"

#include "Geometry/line.hpp"

using Point = Pt<int>;
using Line = Ln<int>;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    Line base;
    cin >> base[0] >> base[1];
    int q;
    cin >> q;
    cout << fixed << setprecision(10);
    while (q--) {
        Point p;
        cin >> p;
        cout << projection<double>(p, base) << "\n";
    }
}
