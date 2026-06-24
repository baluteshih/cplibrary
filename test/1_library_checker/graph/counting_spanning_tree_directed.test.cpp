#define PROBLEM "https://judge.yosupo.jp/problem/counting_spanning_tree_directed"
#include "assumption.hpp"

#include "Numeric/Modint.hpp"
#include "Graph/base.hpp"
#include "Graph/count_spanning_tree.hpp"

using mint = modint998244353;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, m, r;
    std::cin >> n >> m >> r;
    Graph<> G(n);
    while (m--) {
        int u, v;
        std::cin >> u >> v;
        G.add_edge(u, v);
    }
    std::cout << count_spanning_tree<mint>(G, r) << "\n";
}
