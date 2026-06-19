#define PROBLEM "https://judge.yosupo.jp/problem/jump_on_tree"
#include "assumption.hpp"

#include "Tree/TreeTools.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    TreeTools<> tree(n);
    for (int i = 1; i < n; ++i) {
        int u, v;
        std::cin >> u >> v;
        tree.add_edge(u, v);
    }
    tree.build_patable(0);
    while (q--) {
        int s, t, i;
        std::cin >> s >> t >> i;
        if (i > tree.distance(s, t)) std::cout << "-1\n";
        else std::cout << tree.step(s, t, i) << "\n";
    }
}
