#define PROBLEM "https://www.luogu.com.cn/problem/P5055"
#define IGNORE
#include "default_code.hpp"

#include "DataStructure/Treap.hpp"

#define POOL_SIZE 17000000
#include "DataStructure/PoolAllocator.hpp"

struct Value {
    ll sum;
    int sz;
    Value(ll x = 0, int sz_ = 0): sum(x), sz(sz_) {}
    Value operator+(const Value &rhs) const {
        return Value(sum + rhs.sum, sz + rhs.sz);
    }
    int size() const {
        return sz; 
    }
    friend ostream& operator<<(ostream& os, const Value &v) {
        os << v.sum << " " << v.sz;
        return os;
    }
};

using treap = Treap<void, Value, void, true, PoolAllocator, true>;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    vector<treap> tree(n + 1);
    ll lastans = 0;
    for (int i = 1; i <= n; ++i) {
        int v, op;
        cin >> v >> op;
        tree[i] = tree[v];
        if (op == 1) {
            ll p, x;
            cin >> p >> x;
            p ^= lastans, x ^= lastans;
            auto lft = tree[i].split_size(p);
            tree[i].left_merge(treap(Value(x, 1))).left_merge(lft);
        }
        else if (op == 2) {
            ll p;
            cin >> p;
            p ^= lastans;
            auto lft = tree[i].split_size(p - 1);
            tree[i].split_size(1);
            tree[i].left_merge(lft);
        }
        else if (op == 3) {
            ll l, r;
            cin >> l >> r;
            l ^= lastans, r ^= lastans;
            --l;
            tree[i].range_reverse(l, r);
        }
        else {
            ll l, r;
            cin >> l >> r;
            l ^= lastans, r ^= lastans;
            --l;
            lastans = tree[i].range_prod(l, r).sum;
            cout << lastans << "\n";
        }
    }
}
