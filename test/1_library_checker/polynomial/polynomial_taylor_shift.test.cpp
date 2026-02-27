#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_taylor_shift"
#include "default_code.hpp"

#include "Polynomial/shift.hpp"

using mint = modint998244353;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n;
    mint c;
    cin >> n >> c;
    Poly_t a(n);
    for (auto &i : a)
        cin >> i;
    a.shift(c);
    for (int i = 0; i < n; ++i)
        cout << a[i] << " \n"[i + 1 == n]; 
}
