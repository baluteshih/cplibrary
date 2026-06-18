#define PROBLEM "https://judge.yosupo.jp/problem/scc"
#include "assumption.hpp"

#include "Graph/SCC.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    SCC scc(n);
    while (m--) {
        int u, v;
        std::cin >> u >> v;
        scc.add_edge(u, v);
    }
    scc.solve();
    auto ans = scc.components();
    std::cout << ans.size() << "\n";
    for (auto &v : ans) {
        std::cout << v.size();
        for (int i : v)
            std::cout << " " << i;
        std::cout << "\n";
    }
}
