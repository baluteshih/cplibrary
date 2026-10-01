#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_point_set_rectangle_affine_rectangle_sum"
#include "assumption.hpp"

#include "DataStructure/KDTree.hpp"
#include "Numeric/Modint.hpp"
#include "Algebra/Acted_Monoid/sum_and_size-linear_transform.hpp"

using mint = modint998244353;
using kdtree = KDTree<2, long long, sum_and_size<mint>, linear_transform_tag<mint>>;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    kdtree tree;
    std::vector<std::pair<kdtree::Point, sum_and_size<mint>>> arr(n);
    for (auto &[pt, v] : arr)
        std::cin >> pt[0] >> pt[1] >> v;
    auto pts = tree.build(arr);
    while (q--) {
        int op;
        std::cin >> op;
        if (op == 0) {
            kdtree::Point pt;
            sum_and_size<mint> w;
            std::cin >> pt[0] >> pt[1] >> w;
            pts.push_back(tree.insert(pt, w));
        }
        else if (op == 1) {
            int x;
            sum_and_size<mint> w;
            std::cin >> x >> w;
            tree.update_node(pts[x], [&](auto &v) {
                v = w;  
            });
        }
        else if (op == 2) {
            int l, d, r, u;
            std::cin >> l >> d >> r >> u;
            std::cout << tree.query_range(kdtree::Rect(l, d, r - 1, u - 1)) << "\n";
        }
        else {
            int l, d, r, u;
            linear_transform_tag<mint> tag;
            std::cin >> l >> d >> r >> u >> tag.a >> tag.b;
            tree.transform_range(kdtree::Rect(l, d, r - 1, u - 1), tag);
        }
    }
}
