#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"
#include "assumption.hpp"

#include "DataStructure/ZkwSegmentTree.hpp"

struct Value {
    int val;
    Value(int _v = 1e9): val(_v) {}
    Value operator+(const Value &rhs) {
        return Value(std::min(val, rhs.val));
    }
    friend std::ostream& operator<<(std::ostream& os, const Value &v) {
        os << v.val;
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Value &v) {
        is >> v.val;
        return is;
    }
};

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    std::vector<Value> arr(n);
    for (auto &v : arr)
        std::cin >> v;
    ZkwSegmentTree<Value> seg(arr);
    while (q--) {
        int l, r;
        std::cin >> l >> r;
        std::cout << seg.range_prod(l, r) << "\n";
    }
}
