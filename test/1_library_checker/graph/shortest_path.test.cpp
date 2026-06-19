#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"
#include "assumption.hpp"

#include "Graph/Dijkstra.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, m, s, t;
    std::cin >> n >> m >> s >> t;
    Dijkstra<long long> dijk(n);
    while (m--) {
        int u, v, w;
        std::cin >> u >> v >> w;
        dijk.add_edge(u, v, w);
    }
    dijk.solve(s);
    if (!dijk.has_path[t]) {
        std::cout << "-1\n";
        return 0;
    }
    auto path = dijk.path(t);
    std::cout << dijk.dis[t] << " " << int(path.size()) - 1 << "\n";
    for (int i = 0; i + 1 < int(path.size()); ++i) {
        std::cout << path[i] << " " << path[i + 1] << "\n";
    }
}
