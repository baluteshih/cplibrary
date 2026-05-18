#define PROBLEM "https://judge.yosupo.jp/problem/st_numbering"
#include "default_code.hpp"

#include "Graph/BCC.hpp"
#include "Graph/bipolar_orientation.hpp"

void solve() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    if (m == 0) {
        cout << "No\n";
        return;
    }
    UndirectedGraph G(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        G.add_edge(u, v);
    }
    BCC bcc(G);
    bcc.add_edge(s, t);
    bcc.solve();
    if (bcc.nbcc > 1)
        cout << "No\n";
    else {
        cout << "Yes\n";
        auto res = bipolar_orientation(G, s, t);
        vector<int> ans(n);
        for (int i = 0; i < n; ++i) ans[res[i]] = i;
        for (int i = 0; i < n; ++i)
            cout << ans[i] << " \n"[i + 1 == n];
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
