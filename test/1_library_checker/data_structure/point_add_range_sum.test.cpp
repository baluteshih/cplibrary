#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include "assumption.hpp"

#include "DataStructure/SegmentTree.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    std::vector<long long> arr(n);
    for (auto &v : arr)
        std::cin >> v;
    SegmentTree<long long> seg(arr);
    while (q--) {
        int t;
        std::cin >> t;
        if (t == 0) {
            int p, x;
            std::cin >> p >> x;
            seg.transform(p, [&](long long &a) {
                a += x;
            });
        }
        else {
            int l, r;
            std::cin >> l >> r;
            std::cout << seg.range_prod(l, r) << "\n";
        }
    }
}
