#define PROBLEM "https://judge.yosupo.jp/problem/dominatortree"
#include "default_code.hpp"

#include "Graph/dominator_tree.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m, s;
    cin >> n >> m >> s;
    Graph G(n);
    while (m--) {
        int a, b;
        cin >> a >> b;
        G.add_edge(a, b);
    }
    auto ans = dominator_tree(G, s);
    for (int i = 0; i < n; ++i)
        cout << ans[i] << " \n"[i + 1 == n];
}
