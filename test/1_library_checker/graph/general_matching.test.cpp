#define PROBLEM "https://judge.yosupo.jp/problem/general_matching"
#include "assumption.hpp"

#include "Graph/Matching.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    Matching mch(n);
    while (m--) {
        int u, v;
        std::cin >> u >> v;
        mch.add_edge(u, v);
    }
    std::cout << mch.solve() << "\n";
    for (int i = 0; i < n; ++i)
        if (mch.match[i] > i)
            std::cout << i << " " << mch.match[i] << "\n";
}
