#define PROBLEM "https://judge.yosupo.jp/problem/minimum_spanning_tree"
#include "default_code.hpp"

#include "Graph/minimum_spanning_tree.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    UndirectedGraph<int> graph(n);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        graph.add_edge(a, b, c);
    }
    auto res = minimum_spanning_tree(graph);
    ll ans = 0;
    for (int i : res)
        ans += graph.edge(i).weight;
    cout << ans << "\n";
    for (int i = 0; i + 1 < n; ++i)
        cout << res[i] << " \n"[i + 2 == n]; 
}
