#define PROBLEM "https://judge.yosupo.jp/problem/count_points_in_triangle"
#include "default_code.hpp"

#include "Geometry/PointInAngle.hpp"

using Point = Pt<ll>;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m, q;
    cin >> n;
    vector<Point> arr(n);
    for (auto &p : arr)
        cin >> p;
    cin >> m;
    vector<Point> extra(m);
    for (auto &p : extra)
        cin >> p;
    PointInAngle<int, Point> ds(arr, vector<int>(n, 0), extra, vector<int>(m, 1));
    cin >> q;
    while (q--) {
        int x, y, z;
        cin >> x >> y >> z;
        cout << ds.calc_tri(x, y, z) << "\n";
    }
}
