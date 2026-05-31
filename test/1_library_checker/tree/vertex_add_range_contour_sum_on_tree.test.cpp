#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_range_contour_sum_on_tree"
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
    for (int i = 0; i < n; ++i)
        tree.climb(i, [&](auto &ds, int d, [[maybe_unused]] bool prev) {
            ds.modify(d, arr[i]);
        });
    auto range_query = [&](auto &ds, int l, int r) {
        l = max(l, 0), r = min(r, ds.n);
        if (l >= r) return 0LL;
        return ds.range(l, r);
    };
    while (q--) {
        int op, p;
        cin >> op >> p;
        if (op == 0) {
            int x;
            cin >> x;
            tree.climb(p, [&](auto &ds, int d, [[maybe_unused]] bool prev) {
                ds.modify(d, x); 
            });
        }
        else {
            int l, r;
            cin >> l >> r;
            ll ans = 0;
            tree.climb(p, [&](auto &ds, int d, bool prev) {
                ll res = range_query(ds, l - d, r - d);
                if (prev) ans -= res;
                else ans += res;
            });
            cout << ans << "\n";
        }
    }
}
