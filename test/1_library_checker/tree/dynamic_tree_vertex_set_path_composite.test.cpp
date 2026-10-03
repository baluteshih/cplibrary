#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite"
#include "assumption.hpp"

#include "Tree/LinkCutTree.hpp"
#include "Algebra/Monoid/reversable_linear_transform.hpp"
#include "Numeric/Modint.hpp"

using mint = modint998244353;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    std::vector<linear_transform<mint>> arr(n);
    for (auto &v : arr) std::cin >> v;
    LinkCutTree<linear_transform<mint>, reversable_linear_transform<mint>> lct(arr);
    for (int i = 1; i < n; ++i) {
        int u, v;
        std::cin >> u >> v;
        lct.link(u, v);
    }
    while (q--) {
        int op;
        std::cin >> op;
        if (op == 0) {
            int u, v, w, x;
            std::cin >> u >> v >> w >> x;
            lct.cut(u, v);
            lct.link(w, x);
        }
        else if (op == 1) {
            int p;
            linear_transform<mint> x;
            std::cin >> p >> x;
            lct.set_val(p, x);
        }
        else {
            int u, v;
            mint x;
            std::cin >> u >> v >> x;
            std::cout << lct.path_query(u, v).eval(x) << "\n";
        }
    }
}
