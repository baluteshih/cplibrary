#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"
#include "assumption.hpp"

#include "Numeric/Modint.hpp"

#include "DataStructure/SegmentTree.hpp"

using mint = modint998244353;

struct Value {
    mint x, y; 
    Value(mint _x = 0, mint _y = 0): x(_x), y(_y) {}
    Value operator+(const Value &rhs) {
        return Value(x * rhs.x, y * rhs.x + rhs.y);
    }
    friend std::istream& operator>>(std::istream& is, Value &v) {
        is >> v.x >> v.y;
        return is;
    }
    mint apply(mint a) {
        return x * a + y;
    }
};

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    std::vector<Value> arr(n);
    for (auto &v : arr)
        std::cin >> v;
    SegmentTree<Value> seg(arr);
    while (q--) {
        int t;
        std::cin >> t;
        if (t == 0) {
            int p;
            Value v;
            std::cin >> p >> v;
            seg.modify(p, v);
        }
        else {
            int l, r;
            mint x;
            std::cin >> l >> r >> x;
            std::cout << seg.range_prod(l, r).apply(x) << "\n";
        }
    }
}
