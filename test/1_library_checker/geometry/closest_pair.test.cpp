#define PROBLEM "https://judge.yosupo.jp/problem/closest_pair"
#include "default_code.hpp"

#include "Geometry/closest_pair.hpp"

using Point = Pt<ll>;

void solve() {
    int n;
    cin >> n;
    vector<Point> arr(n);
    for (auto &p : arr)
        cin >> p;
    auto [i, j] = closest_pair(arr);
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
