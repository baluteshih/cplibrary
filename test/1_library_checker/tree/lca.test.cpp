#define PROBLEM "https://judge.yosupo.jp/problem/lca"
#include "default_code.hpp"

#include "Tree/TreeTools.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n >> q;
    TreeTools<> tree(n);
    for (int i = 1; i < n; ++i) {
        int p;
        cin >> p;
        tree.add_edge(p, i);
    }
    tree.build_patable(0);
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << tree.lca(u, v) << "\n";
    }
}
