#define PROBLEM "https://judge.yosupo.jp/problem/cycle_detection_undirected"
#include "default_code.hpp"

#include "Graph/base.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    UndirectedGraph graph(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        graph.add_edge(u, v);
    }
    auto [res_v, res_e] = graph.cycle();
    if (res_v.empty()) cout << "-1\n";
    else {
        cout << res_v.size() << "\n";
        for (int i = 0; i < int(res_v.size()); ++i)
            cout << res_v[i] << " \n"[i + 1 == int(res_v.size())];
        for (int i = 0; i < int(res_e.size()); ++i)
            cout << res_e[i] << " \n"[i + 1 == int(res_e.size())];
    }
}
