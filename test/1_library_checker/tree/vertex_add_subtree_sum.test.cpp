#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"
#include "default_code.hpp"

#include "Tree/HeavyLightDecomposition.hpp"
#include "DataStructure/BIT.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n >> q;
    HeavyLightDecomposition<> hld(n);
    vector<int> arr(n);
    for (int &i : arr)
        cin >> i;
    for (int i = 1; i < n; ++i) {
        int p;
        cin >> p;
        hld.add_edge(p, i);
    }
    hld.build();
    vector<ll> weight(n);
    for (int i = 0; i < n; ++i)
        weight[i] = arr[hld.preorder[i]];
    BIT<ll> bit(weight);
    while (q--) {
        int type;
        cin >> type;
        if (type == 0) {
            int p, x;
            cin >> p >> x;
            bit.modify(hld.dfs_in[p], x); 
        }
        else {
            int u;
            cin >> u;
            hld.work_subtree<false>(u, [&](int l, int r) {
                cout << bit.range(l, r) << "\n";
            }); 
        }
    }
}
