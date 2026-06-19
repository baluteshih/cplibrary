#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"
#include "assumption.hpp"

#include "DataStructure/DisjointSet.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    DisjointSet djs(n);
    while (q--) {
        int t, u, v;
        std::cin >> t >> u >> v;
        if (t == 0)
            djs.merge(u, v);
        else
            std::cout << djs.same(u, v) << "\n";
    }
}
