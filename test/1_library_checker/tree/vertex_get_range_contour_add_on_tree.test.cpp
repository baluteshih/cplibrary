#define PROBLEM "https://judge.yosupo.jp/problem/vertex_get_range_contour_add_on_tree"
#include "default_code.hpp"

#include "Tree/CentroidDS/DistanceSolver.hpp"
#include "DataStructure/BIT.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    for (int &i : arr)
        cin >> i;
    DistanceSolver<BIT<ll>> tree(n);
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        tree.add_edge(u, v);
    }
    tree.build();
    auto range_add = [&](auto &ds, int l, int r, int x) {
        l = max(l, 0), r = min(r, ds.n);
        if (l >= r) return;
        ds.modify(l, x);
        ds.modify(r, -x);
    };
    while (q--) {
        int op, p;
        cin >> op >> p;
        if (op == 0) {
            int l, r, x;
            cin >> l >> r >> x;
            tree.climb(p, [&](auto &ds, int d, [[maybe_unused]] bool prev) {
                range_add(ds, l - d, r - d, x);
            });
        }
        else {
            ll ans = arr[p];
            tree.climb(p, [&](auto &ds, int d, bool prev) {
                ll res = ds.prefix(d);
                if (prev) ans -= res;
                else ans += res;
            });
            cout << ans << "\n";
        }
    }
}
