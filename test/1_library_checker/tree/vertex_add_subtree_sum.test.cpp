#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"
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
        int p;
        std::cin >> p;
        hld.add_edge(p, i);
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
            int u;
            std::cin >> u;
            hld.work_subtree<false>(u, [&](int l, int r) {
                std::cout << bit.range(l, r) << "\n";
            }); 
        }
    }
}
