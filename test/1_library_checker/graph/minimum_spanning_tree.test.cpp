#define PROBLEM "https://judge.yosupo.jp/problem/minimum_spanning_tree"
#include "assumption.hpp"

#include "Graph/minimum_spanning_tree.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    UndirectedGraph<int> graph(n);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        std::cin >> a >> b >> c;
        graph.add_edge(a, b, c);
    }
    auto res = minimum_spanning_tree(graph);
    long long ans = 0;
    for (int i : res)
        ans += graph.edge(i).weight;
    std::cout << ans << "\n";
    for (int i = 0; i + 1 < n; ++i)
        std::cout << res[i] << " \n"[i + 2 == n]; 
}
