#define PROBLEM "https://judge.yosupo.jp/problem/range_reverse_range_sum"
#include "default_code.hpp"

#include "DataStructure/Treap.hpp"

struct Value {
    ll sum;
    int sz;
    Value(ll sum_ = 0, int sz_ = 0): sum(sum_), sz(sz_) {}
    Value operator+(const Value &rhs) const {
        return Value(sum + rhs.sum, sz + rhs.sz);
    }
    int size() const {
        return sz; 
    }
    friend ostream& operator<<(ostream& os, const Value &v) {
        os << v.sum;
        return os;
    }
};

using treap = Treap<void, Value, void, true>;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n >> q;
    treap tree;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        tree.push_back(Value(x, 1));
    }
    while (q--) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 0)
            tree.range_reverse(l, r);
        else
            cout << tree.range_prod(l, r) << "\n";
    }
}
