#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_frequency"
#include "default_code.hpp"

#include "DataStructure/PointerSegmentTree.hpp"

using segtree = PointerSegmentTree<int, void, true, DefaultAllocator, true>;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    for (auto &v : arr)
        cin >> v;
    map<int, segtree> mp;
    
    auto get_seg = [&](int x) -> segtree& {
        if (mp.find(x) != mp.end()) return mp[x];
        mp[x] = segtree(n);
        return mp[x];
    };

    for (int i = 0; i < n; ++i)
        get_seg(arr[i]).modify(i, 1);
    for (int i = 1; i <= q; ++i) {
        int type;
        cin >> type;
        if (type == 0) {
            int k, x;
            cin >> k >> x;
            get_seg(arr[k]).modify(k, 0);
            arr[k] = x;
            get_seg(arr[k]).modify(k, 1);
        }
        else {
            int l, r, x;
            cin >> l >> r >> x;
            cout << get_seg(x).range_prod(l, r) << "\n";
        }
    }
}
