#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"
#include "assumption.hpp"

#include "Tree/HeavyLightDecomposition.hpp"
#include "DataStructure/BIT.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    HeavyLightDecomposition<> hld(n);
    std::vector<int> arr(n);
    for (int &i : arr)
        std::cin >> i;
    for (int i = 1; i < n; ++i) {
        int u, v;
        std::cin >> u >> v;
        hld.add_edge(u, v);
    }
    hld.build();
    std::vector<long long> weight(n);
    for (int i = 0; i < n; ++i)
        weight[i] = arr[hld.preorder[i]];
    BIT<long long> bit(weight);
    while (q--) {
        int type;
        std::cin >> type;
        if (type == 0) {
            int p, x;
            std::cin >> p >> x;
            bit.modify(hld.dfs_in[p], x); 
        }
        else {
            int u, v;
            std::cin >> u >> v;
            long long ans = 0;
            hld.work_path<false>(u, v, [&](int l, int r, [[maybe_unused]] bool is_up) {
                ans += bit.range(l, r);
            }); 
            std::cout << ans << "\n";
        }
    }
}
