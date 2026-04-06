#define PROBLEM "https://judge.yosupo.jp/problem/furthest_pair"
#include "default_code.hpp"

#include "Geometry/furthest_pair.hpp"

using Point = Pt<ll>;

void solve() {
    int n;
    cin >> n;
    vector<Point> arr(n);
    for (auto &p : arr)
        cin >> p;
    auto [i, j] = furthest_pair(arr);
    cout << i << " " << j << "\n";
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
