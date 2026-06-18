#define PROBLEM "https://judge.yosupo.jp/problem/st_numbering"
#include "assumption.hpp"

#include "Graph/BCC.hpp"
#include "Graph/bipolar_orientation.hpp"

void solve() {
    int n, m, s, t;
    std::cin >> n >> m >> s >> t;
    if (m == 0) {
        std::cout << "No\n";
        return;
    }
    UndirectedGraph<> G(n);
    while (m--) {
        int u, v;
        std::cin >> u >> v;
        G.add_edge(u, v);
    }
    BCC bcc(G);
    bcc.add_edge(s, t);
    bcc.solve();
    if (bcc.nbcc > 1)
        std::cout << "No\n";
    else {
        std::cout << "Yes\n";
        auto res = bipolar_orientation(G, s, t);
        std::vector<int> ans(n);
        for (int i = 0; i < n; ++i) ans[res[i]] = i;
        for (int i = 0; i < n; ++i)
            std::cout << ans[i] << " \n"[i + 1 == n];
    }
}

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
}
