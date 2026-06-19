#define PROBLEM "https://judge.yosupo.jp/problem/tree_diameter"
#include "assumption.hpp"

#include "Tree/Tree.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n;
    std::cin >> n;
    Tree<long long> tree(n);
    for (int i = 1; i < n; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        tree.add_edge(u, v, w);
    }
    auto dis = tree.distance_edge(0);
    int s = std::ranges::max_element(dis) - dis.begin();
    dis = tree.distance_edge(s);
    int t = std::ranges::max_element(dis) - dis.begin();
    auto res = tree.path(s, t);
    std::cout << dis[t] << " " << res.size() << "\n";
    for (int i = 0; i < int(res.size()); ++i)
        std::cout << res[i] << " \n"[i + 1 == int(res.size())];
}
