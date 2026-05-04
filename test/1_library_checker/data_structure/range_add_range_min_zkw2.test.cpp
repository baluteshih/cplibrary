#define PROBLEM "https://judge.yosupo.jp/problem/range_add_range_min"
#include "default_code.hpp"

#include "DataStructure/ZkwSegmentTree.hpp"

struct Tag {
    ll a;
    Tag(ll _a = 0): a(_a) {}
    Tag operator+(const Tag &rhs) {
        return Tag(a + rhs.a);
    }
    friend ostream& operator<<(ostream& os, const Tag &v) {
        os << v.a;
        return os;
    }
};

struct Value {
    ll val;
    Value(ll _val = 1e18): val(_val) {}
    Value operator+(const Value &rhs) {
        return Value(min(val, rhs.val));
    }
    Value operator+(const Tag &tag) {
        return Value(val + tag.a);
    }
    Value operator-(const Tag &tag) {
        return Value(val - tag.a);
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
    ZkwSegmentTree<Value, Tag, false> seg(arr);
    while (q--) {
        int type, l, r;
        cin >> type >> l >> r;
        if (type == 0) {
            int x;
            cin >> x;
            seg.range_transform(l, r, Tag(x));
        }
        else {
            cout << seg.range_prod(l, r) << "\n";
        }
    }
}
