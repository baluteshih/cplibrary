#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"
#include "default_code.hpp"

#include "DataStructure/SegmentTree.hpp"

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

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<Value> arr(n);
    for (auto &v : arr)
        cin >> v;
    SegmentTree<Value, Tag> seg(arr);
    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int l, r;
            Tag tag;
            cin >> l >> r >> tag.a >> tag.b;
            seg.range_transform(l, r, tag);
        }
        else {
            int l, r;
            cin >> l >> r;
            cout << seg.range_prod(l, r) << "\n";
        }
    }
}
