#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"
#include "default_code.hpp"

#include "Graph/BipartiteMatching.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int l, r, m;
    cin >> l >> r >> m;
    BipartiteMatching mch(l, r);
    while (m--) {
        int u, v;
        cin >> u >> v;
        mch.add_edge(u, v);
    }
    cout << mch.matching() << "\n";
    for (int i = 0; i < l; ++i)
        if (~mch.match_right[i])
            cout << i << " " << mch.match_right[i] << "\n";
}
