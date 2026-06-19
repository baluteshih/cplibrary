#define PROBLEM "https://judge.yosupo.jp/problem/range_reverse_range_sum"
#include "assumption.hpp"

#include "DataStructure/Treap.hpp"

struct Value {
    long long sum;
    int sz;
    Value(long long sum_ = 0, int sz_ = 0): sum(sum_), sz(sz_) {}
    Value operator+(const Value &rhs) const {
        return Value(sum + rhs.sum, sz + rhs.sz);
    }
    int size() const {
        return sz; 
    }
    friend std::ostream& operator<<(std::ostream& os, const Value &v) {
        os << v.sum;
        return os;
    }
};

using treap = Treap<void, Value, void, true>;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    treap tree;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        tree.push_back(Value(x, 1));
    }
    while (q--) {
        int op, l, r;
        std::cin >> op >> l >> r;
        if (op == 0)
            tree.range_reverse(l, r);
        else
            std::cout << tree.range_prod(l, r) << "\n";
    }
}
