#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"
#include "assumption.hpp"

#include "DataStructure/SegmentTree.hpp"
#include "Algebra/Monoid/linear_transform_tag.hpp"

#include "Numeric/Modint.hpp"

using mint = modint998244353;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    std::vector<sum_and_size<mint>> arr(n);
    for (auto &v : arr)
        std::cin >> v;
    SegmentTree<sum_and_size<mint>, linear_transform_tag<mint>> seg(arr);
    while (q--) {
        int t;
        std::cin >> t;
        if (t == 0) {
            int l, r;
            linear_transform_tag<mint> tag;
            std::cin >> l >> r >> tag.a >> tag.b;
            seg.range_transform(l, r, tag);
        }
        else {
            int l, r;
            std::cin >> l >> r;
            std::cout << seg.range_prod(l, r) << "\n";
        }
    }
}
