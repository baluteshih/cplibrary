#define PROBLEM "https://judge.yosupo.jp/problem/biconnected_components"
#include "assumption.hpp"

#include "Graph/BCC.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    BCC bcc(n);
    while (m--) {
        int u, v;
        std::cin >> u >> v;
        bcc.add_edge(u, v);
    }
    bcc.solve();
    std::cout << bcc.nbcc << "\n";
    for (auto &v : bcc.bcc) {
        std::cout << v.size();
        for (int i : v)
            std::cout << " " << i;
        std::cout << "\n";
    }
}
