#define PROBLEM "https://judge.yosupo.jp/problem/tree_diameter"
#include "default_code.hpp"

#include "Tree/Tree.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    Tree<ll> tree(n);
    for (int i = 1; i < n; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        tree.add_edge(u, v, w);
    }
    auto dis = tree.distance_edge(0);
    int s = ranges::max_element(dis) - dis.begin();
    dis = tree.distance_edge(s);
    int t = ranges::max_element(dis) - dis.begin();
    auto res = tree.path(s, t);
    cout << dis[t] << " " << res.size() << "\n";
    for (int i = 0; i < SZ(res); ++i)
        cout << res[i] << " \n"[i + 1 == SZ(res)];
}
