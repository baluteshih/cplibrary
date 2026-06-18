#define PROBLEM "https://judge.yosupo.jp/problem/cycle_detection_undirected"
#include "assumption.hpp"

#include "Graph/base.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    UndirectedGraph<> graph(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph.add_edge(u, v);
    }
    auto [res_v, res_e] = graph.cycle();
    if (res_v.empty()) std::cout << "-1\n";
    else {
        std::cout << res_v.size() << "\n";
        for (int i = 0; i < int(res_v.size()); ++i)
            std::cout << res_v[i] << " \n"[i + 1 == int(res_v.size())];
        for (int i = 0; i < int(res_e.size()); ++i)
            std::cout << res_e[i] << " \n"[i + 1 == int(res_e.size())];
    }
}
