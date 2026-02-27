#define PROBLEM "https://judge.yosupo.jp/problem/shift_of_sampling_points_of_polynomial"
#include "default_code.hpp"

#include "Polynomial/lagrange_interpolate_iota.hpp"

using mint = modint998244353;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m;
    mint c;
    cin >> n >> m >> c;
    Poly_t a(n);
    for (auto &i : a)
        cin >> i;
    auto res = lagrange_interpolate_iota(a, c, m);
    for (int i = 0; i < m; ++i)
        cout << res[i] << " \n"[i + 1 == m];
}
