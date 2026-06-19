#define PROBLEM "https://judge.yosupo.jp/problem/lca"
#include "assumption.hpp"

#include "Tree/TreeTools.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    TreeTools<> tree(n);
    for (int i = 1; i < n; ++i) {
        int p;
        std::cin >> p;
        tree.add_edge(p, i);
    }
    tree.build_patable(0);
    while (q--) {
        int u, v;
        std::cin >> u >> v;
        std::cout << tree.lca(u, v) << "\n";
    }
}
