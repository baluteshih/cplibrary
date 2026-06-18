#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"
#include "assumption.hpp"

#include "Graph/BipartiteMatching.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int l, r, m;
    std::cin >> l >> r >> m;
    BipartiteMatching mch(l, r);
    while (m--) {
        int u, v;
        std::cin >> u >> v;
        mch.add_edge(u, v);
    }
    std::cout << mch.matching() << "\n";
    for (int i = 0; i < l; ++i)
        if (~mch.match_right[i])
            std::cout << i << " " << mch.match_right[i] << "\n";
}
