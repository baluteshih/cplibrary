#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_point_get"
#include "default_code.hpp"

#include "DataStructure/SegmentTree.hpp"

#include "Numeric/Modint.hpp"

using mint = modint998244353;

struct Tag {
    mint mul, add;
    Tag(mint _mul = 1, mint _add = 0): mul(_mul), add(_add) {}
    Tag operator+(const Tag &rhs) {
        return Tag(mul * rhs.mul, rhs.mul * add + rhs.add);
    }
};

struct Value {
    mint val;
    Value(mint _val = 0): val(_val) {}
    Value operator+(const Value &rhs) {
        return *this;
    }
    Value operator+(const Tag &tag) {
        return Value(tag.mul * val + tag.add);
    }
    friend ostream& operator<<(ostream& os, const Value &v) {
        os << v.val;
        return os;
    }
    friend istream& operator>>(istream& is, Value &v) {
        is >> v.val;
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
            cin >> l >> r >> tag.mul >> tag.add;
            seg.range_transform(l, r, tag);
        }
        else {
            int x;
            cin >> x;
            cout << seg.get(x) << "\n";
        }
    }
}
