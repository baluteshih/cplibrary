#define PROBLEM "https://judge.yosupo.jp/problem/biconnected_components"
#include "default_code.hpp"

#include "Graph/BCC.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    BCC bcc(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        bcc.add_edge(u, v);
    }
    bcc.solve();
    cout << bcc.nbcc << "\n";
    for (auto &v : bcc.bcc) {
        cout << SZ(v);
        for (int i : v)
            cout << " " << i;
        cout << "\n";
    }
}
