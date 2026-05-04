#define PROBLEM "https://judge.yosupo.jp/problem/unionfind_with_potential_non_commutative_group"
#include "default_code.hpp"

#include "DataStructure/PotentialDisjointSet.hpp"
#include "Numeric/Modint.hpp"
#include "Matrix/Matrix.hpp"

using mint = modint998244353;

struct Value {
    Matrix<mint> val;
    Value(Matrix<mint> mat = Matrix<mint>::identity(2)): val(mat) {}
    Value operator+(const Value &rhs) {
        return Value(val * rhs.val);
    }
    Value operator-(const Value &rhs) {
        return Value(val * rhs.val.inv().second);
    }
    bool operator==(const Value &rhs) const {
        return val == rhs.val;
    }
    friend istream& operator>>(istream& is, Value &v) {
        for (auto &vec : v.val)
            for (auto &x : vec)
                is >> x;
        return is;
    }
    friend ostream& operator<<(ostream& os, const Value &v) {
        os << v.val[0][0] << " " << v.val[0][1] << " " << v.val[1][0] << " " << v.val[1][1];
        return os;
    }
};

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n >> q;
    PotentialDisjointSet<Value> djs(n);
    while (q--) {
        int t, u, v;
        cin >> t >> u >> v;
        if (t == 0) {
            bool succ = true;
            Value x;
            cin >> x;
            if (djs.same(u, v)) succ = (djs.diff(v, u) == x);
            else djs.merge(v, u, x);
            cout << succ << "\n";
        }
        else {
            if (djs.same(u, v)) cout << djs.diff(v, u) << "\n";
            else cout << "-1\n";
        }
    }
}
