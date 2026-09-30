#define PROBLEM "https://judge.yosupo.jp/problem/range_add_range_min"
#include "assumption.hpp"

#include "DataStructure/ZkwSegmentTree.hpp"
#include "Algebra/Acted_Monoid/min_v-add.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    std::vector<min_v<long long>> arr(n);
    for (auto &v : arr)
        std::cin >> v;
    ZkwSegmentTree<min_v<long long>, add_tag<long long>> seg(arr);
    while (q--) {
        int type, l, r;
        std::cin >> type >> l >> r;
        if (type == 0) {
            int x;
            std::cin >> x;
            seg.range_transform(l, r, add_tag<long long>(x));
        }
        else {
            std::cout << seg.range_prod(l, r) << "\n";
        }
    }
}
