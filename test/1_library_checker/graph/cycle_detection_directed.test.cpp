#define PROBLEM "https://judge.yosupo.jp/problem/cycle_detection"
#include "assumption.hpp"

#include "Graph/base.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    Graph graph(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph.add_edge(u, v);
    }
    auto [_, res] = graph.cycle();
    if (res.empty()) std::cout << "-1\n";
    else {
        std::cout << res.size() << "\n";
        for (int eid : res)
            std::cout << eid << "\n";
    }
}
