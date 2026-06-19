#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_frequency"
#include "assumption.hpp"

#include "DataStructure/PointerSegmentTree.hpp"

using segtree = PointerSegmentTree<int, void, true, DefaultAllocator, true>;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    std::vector<int> arr(n);
    for (auto &v : arr)
        std::cin >> v;
    std::map<int, segtree> mp;
    
    auto get_seg = [&](int x) -> segtree& {
        if (mp.find(x) != mp.end()) return mp[x];
        mp[x] = segtree(n);
        return mp[x];
    };

    for (int i = 0; i < n; ++i)
        get_seg(arr[i]).modify(i, 1);
    for (int i = 1; i <= q; ++i) {
        int type;
        std::cin >> type;
        if (type == 0) {
            int k, x;
            std::cin >> k >> x;
            get_seg(arr[k]).modify(k, 0);
            arr[k] = x;
            get_seg(arr[k]).modify(k, 1);
        }
        else {
            int l, r, x;
            std::cin >> l >> r >> x;
            std::cout << get_seg(x).range_prod(l, r) << "\n";
        }
    }
}
