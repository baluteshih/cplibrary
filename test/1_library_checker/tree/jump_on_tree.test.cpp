#define PROBLEM "https://judge.yosupo.jp/problem/jump_on_tree"
#include "default_code.hpp"

#include "Tree/TreeTools.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n >> q;
    TreeTools tree(n);
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        tree.add_edge(u, v);
    }
    tree.build_patable(0);
    while (q--) {
        int s, t, i;
        cin >> s >> t >> i;
        if (i > tree.distance(s, t)) cout << "-1\n";
        else cout << tree.step(s, t, i) << "\n";
    }
}
