#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_of_formal_power_series"
#include "default_code.hpp"

#include "Polynomial/Sqrt.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    Poly_t a(n);
    for (auto &i : a)
        cin >> i;
    if (!a.has_sqrt())
        cout << "-1\n";
    else {
        a = a.Sqrt();
        for (int i = 0; i < SZ(a); ++i)
            cout << a[i] << " \n"[i + 1 == SZ(a)];
    }
}
