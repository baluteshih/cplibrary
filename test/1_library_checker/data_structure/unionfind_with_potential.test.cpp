#define PROBLEM "https://judge.yosupo.jp/problem/unionfind_with_potential"
#include "assumption.hpp"

#include "DataStructure/PotentialDisjointSet.hpp"

#include "Numeric/Modint.hpp"

using mint = modint998244353;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    PotentialDisjointSet<mint> djs(n);
    while (q--) {
        int t, u, v;
        std::cin >> t >> u >> v;
        if (t == 0) {
            bool succ = true;
            mint x;
            std::cin >> x;
            if (djs.same(u, v)) succ = (djs.diff(u, v) == x);
            else djs.merge(u, v, x);
            std::cout << succ << "\n";
        }
        else {
            if (djs.same(u, v)) std::cout << djs.diff(u, v) << "\n";
            else std::cout << "-1\n";
        }
    }
}
