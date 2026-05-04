#define PROBLEM "https://judge.yosupo.jp/problem/primitive_root"
#include "default_code.hpp"

#include "Numeric/primitive_root.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int q;
    cin >> q;
    while (q--) {
        ll p;
        cin >> p;
        cout << primitive_root(p) << "\n";
    }
}
