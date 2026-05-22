#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite_large_array"
#include "default_code.hpp"

#include "Numeric/Modint.hpp"
#include "DataStructure/PointerSegmentTree.hpp"

using mint = modint998244353;

struct Value {
    mint x, y; 
    Value(mint _x = 1, mint _y = 0): x(_x), y(_y) {}
    Value operator+(const Value &rhs) {
        return Value(x * rhs.x, y * rhs.x + rhs.y);
    }
    friend istream& operator>>(istream& is, Value &v) {
        is >> v.x >> v.y;
        return is;
    }
    mint apply(mint a) {
        return x * a + y;
    }
};


int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n >> q;
    PointerSegmentTree<Value, void, true, DefaultAllocator, true> seg(n);
    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int p;
            Value v;
            cin >> p >> v;
            seg.modify(p, v);
        }
        else {
            int l, r;
            mint x;
            cin >> l >> r >> x;
            cout << seg.range_prod(l, r).apply(x) << "\n";
        }
    }
}
