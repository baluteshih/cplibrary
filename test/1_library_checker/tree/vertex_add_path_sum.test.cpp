#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"
#include "default_code.hpp"

#include "Tree/HeavyLightDecomposition.hpp"
#include "DataStructure/BIT.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n >> q;
    BIT<ll> bit(n);
    HeavyLightDecomposition<> hld(n);
    vector<int> arr(n);
    for (int &i : arr)
        cin >> i;
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        hld.add_edge(u, v);
    }
    hld.build();
    vector<ll> weight(n);
    for (int i = 0; i < n; ++i)
        weight[i] = arr[hld.preorder[i]];
    bit.initialize(weight);
    while (q--) {
        int type;
        cin >> type;
        if (type == 0) {
            int p, x;
            cin >> p >> x;
            bit.modify(hld.dfs_in[p], x); 
        }
        else {
            int u, v;
            cin >> u >> v;
            ll ans = 0;
            hld.work_path<false>(u, v, [&](int l, int r, [[maybe_unused]] bool is_up) {
                ans += bit.range(l, r);
            }); 
            cout << ans << "\n";
        }
    }
}
