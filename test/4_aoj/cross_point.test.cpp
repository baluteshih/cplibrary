#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_C"
#include "default_code.hpp"

#include "Geometry/line.hpp"

using Point = Pt<int>;
using Line = Ln<int>;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int q;
    cin >> q;
    cout << fixed << setprecision(10);
    while (q--) {
        Line l1, l2;
        cin >> l1[0] >> l1[1] >> l2[0] >> l2[1];
        cout << lineIntersection(l1, l2) << "\n";
    }
}
