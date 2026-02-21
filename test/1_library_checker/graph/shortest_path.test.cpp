#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"
#include "default_code.hpp"

#include "Graph/Dijkstra.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    Dijkstra<ll> dijk(n);
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        dijk.add_edge(u, v, w);
    }
    dijk.solve(s);
    if (!dijk.has_path[t]) {
        cout << "-1\n";
        return 0;
    }
    auto path = dijk.path(t);
    cout << dijk.dis[t] << " " << SZ(path) - 1 << "\n";
    for (int i = 0; i + 1 < SZ(path); ++i) {
        cout << path[i] << " " << path[i + 1] << "\n";
    }
}
