#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum"
#include "default_code.hpp"

#include "Numeric/Modint.hpp"
#include "DataStructure/Treap.hpp"

using mint = modint998244353;

struct Tag {
    mint a, b;
    Tag(mint _a = 1, mint _b = 0): a(_a), b(_b) {}
    Tag operator+(const Tag &rhs) {
        return Tag(a * rhs.a, rhs.a * b + rhs.b);
    }
};

struct Value {
    mint val;
    int sz;
    Value(mint a = 0, int b = 0): val(a), sz(b) {}
    Value operator+(const Value &rhs) const {
        return Value(val + rhs.val, sz + rhs.sz);
    }
    Value operator+(const Tag &tag) const {
        return Value(tag.a * val + tag.b * sz, sz);
    }
    int size() const {
        return sz; 
    }
    static Value get(int l, int r) {
        return Value(0, r - l);
    }
    friend ostream& operator<<(ostream& os, const Value &v) {
        os << v.val;
        return os;
    }
    friend istream& operator>>(istream& is, Value &v) {
        is >> v.val;
        v.sz = 1;
        return is;
    }
};

using treap = Treap<void, Value, Tag, true>;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n >> q;
    treap tree;
    for (int i = 0; i < n; ++i) {
        Value v;
        cin >> v;
        tree.push_back(v);
    }
    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int i;
            Value v;
            cin >> i >> v;
            auto lft = tree.split_size(i);
            tree.left_merge(treap(v)).left_merge(lft);
        }
        else if (t == 1) {
            int i;
            cin >> i;
            tree.erase<false>(tree.kth(i));
        }
        else if (t == 2) {
            int l, r;
            cin >> l >> r;
            tree.range_reverse(l, r);
        }
        else if (t == 3) {
            int l, r;
            Tag tag;
            cin >> l >> r >> tag.a >> tag.b;
            tree.range_transform(l, r, tag);
        }
        else {
            int l, r;
            cin >> l >> r;
            cout << tree.range_prod(l, r) << "\n";
        }
    }
}
