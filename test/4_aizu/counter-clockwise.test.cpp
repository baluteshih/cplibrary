#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_C"
#include "default_code.hpp"

#include "Geometry/line.hpp"

using Point = Pt<int>;
using Line = Ln<int>;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    Point p0, p1;
    cin >> p0 >> p1;
    int q;
    cin >> q;
    while (q--) {
        Point p2;
        cin >> p2;
        int res = side(p0, p1, p2);
        if (res == 1) cout << "COUNTER_CLOCKWISE\n";
        else if (res == -1) cout << "CLOCKWISE\n";
        else {
            if (point_on_seg(p2, Line(p0, p1))) cout << "ON_SEGMENT\n";
            else if (point_on_seg(p1, Line(p0, p2))) cout << "ONLINE_FRONT\n";
            else cout << "ONLINE_BACK\n";
        }
    }
}
