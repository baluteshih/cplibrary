#define PROBLEM "https://judge.yosupo.jp/problem/connected_components_of_complement_graph"
#include "assumption.hpp"

#include "Graph/base.hpp"
#include "Graph/complement_bfs.hpp"
#include "DataStructure/DisjointSet.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    UndirectedGraph<> G(n);
    while (m--) {
        int u, v;
        std::cin >> u >> v;
        G.add_edge(u, v);
    }
    auto parent = complement_bfs(G);
    DisjointSet djs(n);
    for (int i = 0; i < n; ++i)
        djs.merge(parent[i], i);
    auto groups = djs.groups();
    std::cout << groups.size() << "\n";
    for (auto &v : groups) {
        std::cout << v.size();
        for (int i : v) std::cout << " " << i;
        std::cout << "\n";
    }
}
