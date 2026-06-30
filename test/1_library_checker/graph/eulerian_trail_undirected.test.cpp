#define PROBLEM "https://judge.yosupo.jp/problem/eulerian_trail_undirected"
#include "assumption.hpp"

#include "Graph/eulerian_trail.hpp"

void solve() {
    int n, m;
    std::cin >> n >> m;
    UndirectedGraph<> G(n);
    while (m--) {
        int u, v;
        std::cin >> u >> v;
        G.add_edge(u, v);
    }
    auto [vertices, edges] = eulerian_trail(G);
    if (vertices.empty()) std::cout << "No\n";
    else {
        std::cout << "Yes\n";
        for (int i = 0; i < int(vertices.size()); ++i)
            std::cout << vertices[i] << " \n"[i + 1 == int(vertices.size())];
        for (int i = 0; i < int(edges.size()); ++i)
            std::cout << edges[i] << " \n"[i + 1 == int(edges.size())];
    }
}

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
}
