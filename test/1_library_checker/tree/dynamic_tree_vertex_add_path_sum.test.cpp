#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_path_sum"
#include "assumption.hpp"

#include "Tree/LinkCutTree.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    std::vector<long long> arr(n);
    for (auto &v : arr) std::cin >> v;
    LinkCutTree<long long, long long> lct(arr);
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
            int p, x;
            std::cin >> p >> x;
            lct.transform(p, [&](auto &v) {
                v += x; 
            });
        }
        else {
            int u, v;
            std::cin >> u >> v;
            std::cout << lct.path_query(u, v) << "\n";
        }
    }
}
