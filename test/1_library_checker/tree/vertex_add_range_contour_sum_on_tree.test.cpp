#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_range_contour_sum_on_tree"
#include "assumption.hpp"

#include "Tree/CentroidDS/DistanceSolver.hpp"
#include "DataStructure/BIT.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    std::vector<int> arr(n);
    for (int &i : arr)
        std::cin >> i;
    DistanceSolver<BIT<long long>> tree(n);
    for (int i = 1; i < n; ++i) {
        int u, v;
        std::cin >> u >> v;
        tree.add_edge(u, v);
    }
    tree.build();
    for (int i = 0; i < n; ++i)
        tree.climb(i, [&](auto &ds, int d, [[maybe_unused]] bool prev) {
            ds.modify(d, arr[i]);
        });
    auto range_query = [&](auto &ds, int l, int r) {
        l = std::max(l, 0), r = std::min(r, ds.n);
        if (l >= r) return 0ll;
        return ds.range(l, r);
    };
    while (q--) {
        int op, p;
        std::cin >> op >> p;
        if (op == 0) {
            int x;
            std::cin >> x;
            tree.climb(p, [&](auto &ds, int d, [[maybe_unused]] bool prev) {
                ds.modify(d, x); 
            });
        }
        else {
            int l, r;
            std::cin >> l >> r;
            long long ans = 0;
            tree.climb(p, [&](auto &ds, int d, bool prev) {
                long long res = range_query(ds, l - d, r - d);
                if (prev) ans -= res;
                else ans += res;
            });
            std::cout << ans << "\n";
        }
    }
}
