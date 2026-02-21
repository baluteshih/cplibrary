#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include "default_code.hpp"

#include "DataStructure/SegmentTree.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<ll> arr(n);
    for (auto &v : arr)
        cin >> v;
    SegmentTree<ll> seg(arr);
    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int p, x;
            cin >> p >> x;
            seg.transform(p, [&](ll &a) {
                a += x;
            });
        }
        else {
            int l, r;
            cin >> l >> r;
            cout << seg.range_prod(l, r) << "\n";
        }
    }
}
