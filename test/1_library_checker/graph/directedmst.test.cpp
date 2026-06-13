#define PROBLEM "https://judge.yosupo.jp/problem/directedmst"
#include "default_code.hpp"

#include "Graph/minimum_arborescence.hpp"
#include "Tree/Tree.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m, s;
    cin >> n >> m >> s;
    Graph<true, ll> G(n);
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        G.add_edge(u, v, w);
    }
    if (n == 1)
        return cout << "0\n0\n", 0;
    auto res = minimum_arborescence(G, s);
    assert(!res.empty());
    ll sum = 0;
    Tree tree(n);
    for (int i : res) {
        tree.add_edge(G.edge(i).from, G.edge(i).to);
        sum += G.edge(i).weight;
    }
    tree.traverse(s);
    cout << sum << "\n";
    for (int i = 0; i < n; ++i)
        cout << tree.parent(i) << " \n"[i + 1 == n];
}
