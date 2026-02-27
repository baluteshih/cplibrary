#define PROBLEM "https://judge.yosupo.jp/problem/two_edge_connected_components"
#include "default_code.hpp"

#include "Graph/ECC.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    ECC ecc(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        ecc.add_edge(u, v);
    }
    ecc.solve();
    auto ans = ecc.components();
    cout << SZ(ans) << "\n";
    for (auto &v : ans) {
        cout << SZ(v);
        for (int i : v)
            cout << " " << i;
        cout << "\n";
    }
}
