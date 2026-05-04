#define PROBLEM "https://judge.yosupo.jp/problem/line_add_get_min"
#include "default_code.hpp"

#include "Misc/DynamicHull.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n >> q;
    DynamicHull<ll> hull;
    for (int i = 0; i < n; ++i) {
        ll a, b;
        cin >> a >> b;
        hull.addline(-a, -b);
    }
    while (q--) {
        int type;
        cin >> type;
        if (type == 0) {
            ll a, b;
            cin >> a >> b;
            hull.addline(-a, -b);
        }
        else {
            ll p;
            cin >> p;
            cout << -hull.query(p) << "\n";
        }
    }
}
