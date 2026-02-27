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
    vector<vector<int>> ans(scc.nscc);
    for (int i = 0; i < n; ++i)
        ans[scc.bln[i]].push_back(i);
    reverse(ALL(ans));
    cout << SZ(ans) << "\n";
    for (auto &v : ans) {
        cout << SZ(v);
        for (int i : v)
            cout << " " << i;
        cout << "\n";
    }
}
