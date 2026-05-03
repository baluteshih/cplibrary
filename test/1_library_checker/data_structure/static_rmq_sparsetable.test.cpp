#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"
#include "default_code.hpp"

#include "DataStructure/SparseTable.hpp"

struct Value {
    int val;
    Value(int _v = 2'000'000'000): val(_v) {}
    Value operator+(const Value &rhs) {
        return Value(min(val, rhs.val));
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
    for (auto &i : arr)
        cin >> i;
    SparseTable table(arr);
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << table.range_prod(l, r) << "\n";
    }
}
