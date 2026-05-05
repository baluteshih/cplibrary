#define PROBLEM "https://judge.yosupo.jp/problem/persistent_range_affine_range_sum"
#include "default_code.hpp"

#include "DataStructure/PointerSegmentTree.hpp"

#include "Numeric/Modint.hpp"

using mint = modint998244353;

struct Tag {
    mint a, b;
    Tag(mint _a = 1, mint _b = 0): a(_a), b(_b) {}
    Tag operator+(const Tag &rhs) {
        return Tag(a * rhs.a, rhs.a * b + rhs.b);
    }
};

struct Value {
    mint mul;
    int add;
    Value(mint a = 0, int b = 1): mul(a), add(b) {}
    Value operator+(const Value &rhs) {
        return Value(mul + rhs.mul, add + rhs.add);
    }
    Value operator+(const Tag &tag) {
        return Value(tag.a * mul + tag.b * add, add);
    }
    friend ostream& operator<<(ostream& os, const Value &v) {
        os << v.mul;
        return os;
    }
    friend istream& operator>>(istream& is, Value &v) {
        is >> v.mul;
        v.add = 1;
        return is;
    }
};

using segtree = PointerSegmentTree<Value, Tag, true, DefaultAllocator, false, true>;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<Value> arr(n);
    for (auto &v : arr)
        cin >> v;
    vector<segtree> seg(q + 1);
    seg[0] = segtree(arr);
    for (int i = 1; i <= q; ++i) {
        int k, t;
        cin >> t >> k;
        ++k;
        seg[i] = seg[k];
        if (t == 0) {
            int l, r;
            Tag tag;
            cin >> l >> r >> tag.a >> tag.b;
            seg[i].range_transform(l, r, tag);
        }
        else if (t == 1) {
            int s, l, r;
            cin >> s >> l >> r;
            ++s;
            if (i != s) seg[i].range_copy(l, r, seg[s]);
        }
        else {
            int l, r;
            cin >> l >> r;
            cout << seg[i].range_prod(l, r) << "\n";
        }
    }
}
