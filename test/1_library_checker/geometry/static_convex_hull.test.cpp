#define PROBLEM "https://judge.yosupo.jp/problem/static_convex_hull"
#include "default_code.hpp"

#include "Geometry/convex_hull.hpp"

using Point = Pt<ll>;

void solve() {
    int n;
    cin >> n;
    vector<Point> dots(n);
    for (auto &p : dots)
        cin >> p;
    auto hull = convex_hull(dots);
    cout << hull.size() << "\n";
    for (auto p : hull)
        cout << p << "\n";
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
