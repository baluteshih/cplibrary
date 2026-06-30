#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"
#include "assumption.hpp"

#include "DataStructure/SparseTable.hpp"

struct Value {
    int val;
    Value(int _v = 2'000'000'000): val(_v) {}
    Value operator+(const Value &rhs) const {
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
    for (auto &i : arr)
        std::cin >> i;
    SparseTable<Value> table(arr);
    while (q--) {
        int l, r;
        std::cin >> l >> r;
        std::cout << table.range_prod(l, r) << "\n";
    }
}
