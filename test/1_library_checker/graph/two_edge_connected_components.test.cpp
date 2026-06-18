#define PROBLEM "https://judge.yosupo.jp/problem/two_edge_connected_components"
#include "assumption.hpp"

#include "Graph/ECC.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    ECC ecc(n);
    while (m--) {
        int u, v;
        std::cin >> u >> v;
        ecc.add_edge(u, v);
    }
    ecc.solve();
    auto ans = ecc.components();
    std::cout << ans.size() << "\n";
    for (auto &v : ans) {
        std::cout << v.size();
        for (int i : v)
            std::cout << " " << i;
        std::cout << "\n";
    }
}
