#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_formal_power_series"
#include "default_code.hpp"

#include "Polynomial/Polynomial.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    Poly_t a(n);
    for (auto &i : a)
        cin >> i;
    a = a.Inv();
    for (int i = 0; i < SZ(a); ++i)
        cout << a[i] << " \n"[i + 1 == SZ(a)];
}
