#define PROBLEM "https://judge.yosupo.jp/problem/counting_eulerian_circuits"
#include "assumption.hpp"

#include "Numeric/Modint.hpp"
#include "Graph/count_eulerian_circuits.hpp"

using mint = modint998244353;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    Graph G(n);
    while (m--) {
        int u, v;
        std::cin >> u >> v;
        G.add_edge(u, v);
    }
    std::cout << count_eulerian_circuits<mint>(G) << "\n"; 
}
