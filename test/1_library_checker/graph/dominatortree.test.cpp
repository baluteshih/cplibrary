#define PROBLEM "https://judge.yosupo.jp/problem/dominatortree"
#include "assumption.hpp"

#include "Graph/dominator_tree.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, m, s;
    std::cin >> n >> m >> s;
    Graph G(n);
    while (m--) {
        int a, b;
        std::cin >> a >> b;
        G.add_edge(a, b);
    }
    auto ans = dominator_tree(G, s);
    for (int i = 0; i < n; ++i)
        std::cout << ans[i] << " \n"[i + 1 == n];
}
