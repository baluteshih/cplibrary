#define PROBLEM "https://judge.yosupo.jp/problem/ordered_set"
#include "default_code.hpp"

#include "DataStructure/OrderedSet.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    for (int &i : arr)
        cin >> i;
    vector<int> vals(arr);
    vector<pii> qry(q);
    for (auto &[t, x] : qry) {
        cin >> t >> x;
        if (t == 0 || t == 1)
            vals.push_back(x);
    }
    vals.push_back(0);
    OrderedSet<int> ord(vals);
    for (int i : arr)
        ord.insert(i);
    for (auto &[t, x] : qry) {
        if (t == 0) ord.insert(x);
        else if (t == 1) ord.erase(x);
        else if (t == 2) {
            int res = ord.kth(x - 1);
            if (res != -1) res = ord[res]; 
            cout << res << "\n";
        }
        else if (t == 3)
            cout << ord.leq_count(x) << "\n";
        else if (t == 4) {
            int res = ord.leq(x);
            if (res != -1) res = ord[res]; 
            cout << res << "\n";
        }
        else {
            int res = ord.geq(x);
            if (res != -1) res = ord[res]; 
            cout << res << "\n";
        }
    }
}
