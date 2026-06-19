#define PROBLEM "https://judge.yosupo.jp/problem/vertex_get_range_contour_add_on_tree"
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
    auto range_add = [&](auto &ds, int l, int r, int x) {
        l = std::max(l, 0), r = std::min(r, ds.n);
        if (l >= r) return;
        ds.modify(l, x);
        ds.modify(r, -x);
    };
    while (q--) {
        int op, p;
        std::cin >> op >> p;
        if (op == 0) {
            int l, r, x;
            std::cin >> l >> r >> x;
            tree.climb(p, [&](auto &ds, int d, [[maybe_unused]] bool prev) {
                range_add(ds, l - d, r - d, x);
            });
        }
        else {
            long long ans = arr[p];
            tree.climb(p, [&](auto &ds, int d, bool prev) {
                long long res = ds.prefix(d);
                if (prev) ans -= res;
                else ans += res;
            });
            std::cout << ans << "\n";
        }
    }
}
