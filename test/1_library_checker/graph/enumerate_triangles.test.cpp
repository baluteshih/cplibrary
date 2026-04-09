#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_triangles"
#include "default_code.hpp"

#include "Graph/enumerate_c3.hpp"
#include "Numeric/Modint.hpp"

using mint = modint998244353;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    std::vector<mint> num(n);
    for (auto &x : num)
        cin >> x;
    UndirectedGraph graph(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        graph.add_edge(u, v);
    }
    mint ans = 0;
    enumerate_c3(graph, [&](int x, int y, int z) {
        ans += num[x] * num[y] * num[z];
    });
    cout << ans << "\n";
}
