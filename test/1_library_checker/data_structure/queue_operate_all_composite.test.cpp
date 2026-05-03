#define PROBLEM "https://judge.yosupo.jp/problem/queue_operate_all_composite"
#include "default_code.hpp"

#include "Numeric/Modint.hpp"
#include "DataStructure/SwagQueue.hpp"

using mint = modint998244353;

struct Value {
    mint a, b;
    Value(mint _a = 1, mint _b = 0): a(_a), b(_b) {}
    Value operator+(const Value &rhs) {
        return Value(a * rhs.a, rhs.a * b + rhs.b);
    }
    mint get_val(mint x) {
        return a * x + b;
    }
};

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int q;
    cin >> q;
    SwagQueue<Value> que;
    while (q--) {
        int type;
        cin >> type;
        if (type == 0) {
            mint a, b;
            cin >> a >> b;
            que.push(Value(a, b));
        }
        else if (type == 1) {
            que.pop();
        }
        else {
            mint x;
            cin >> x;
            cout << que.prod().get_val(x) << "\n";
        }
    }
}
