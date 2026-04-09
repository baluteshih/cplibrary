#define PROBLEM "https://judge.yosupo.jp/problem/cycle_detection"
#include "default_code.hpp"

#include "Graph/base.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    Graph graph(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        graph.add_edge(u, v);
    }
    auto [_, res] = graph.cycle();
    if (res.empty()) cout << "-1\n";
    else {
        cout << res.size() << "\n";
        for (int eid : res)
            cout << eid << "\n";
    }
}
