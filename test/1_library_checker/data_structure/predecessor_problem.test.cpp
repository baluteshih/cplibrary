#define PROBLEM "https://judge.yosupo.jp/problem/predecessor_problem"
#include "default_code.hpp"

#include "DataStructure/SegmentTree.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, q;
    string t;
    cin >> n >> q >> t;
    vector<int> init(n);
    for (int i = 0; i < n; ++i)
        init[i] = t[i] == '1';
    SegmentTree<int> seg(init);
    while (q--) {
        int type, k;
        cin >> type >> k;
        if (type == 0) {
            seg.modify(k, 1);  
        }
        else if (type == 1) {
            seg.modify(k, 0); 
        }
        else if (type == 2) {
            cout << seg.get(k) << "\n";
        }
        else if (type == 3) {
            int res = seg.range_left_search([&](int sz) {
                return sz > 0;  
            }, k, n); 
            if (res == n) res = -1;
            cout << res << "\n";
        }
        else {
            int res = seg.range_right_search([&](int sz) {
                return sz > 0; 
            }, -1, k);
            cout << res << "\n";
        }
    }
}
