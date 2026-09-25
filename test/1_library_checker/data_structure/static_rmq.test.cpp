#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"
#include "assumption.hpp"

#include "DataStructure/SegmentTree.hpp"
#include "Algebra/Monoid/min_v.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    std::vector<min_v<int>> arr(n);
    for (auto &v : arr)
        std::cin >> v;
    SegmentTree<min_v<int>> seg(arr);
    while (q--) {
        int l, r;
        std::cin >> l >> r;
        std::cout << seg.range_prod(l, r) << "\n";
    }
}
