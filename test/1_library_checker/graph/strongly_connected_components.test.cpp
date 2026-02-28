#define PROBLEM "https://judge.yosupo.jp/problem/scc"
#include "default_code.hpp"

#include "Graph/SCC.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    SCC scc(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        scc.add_edge(u, v);
    }
    scc.solve();
    auto ans = scc.components();
    cout << SZ(ans) << "\n";
    for (auto &v : ans) {
        cout << SZ(v);
        for (int i : v)
            cout << " " << i;
        cout << "\n";
    }
}
