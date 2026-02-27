#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_interpolation"
#include "default_code.hpp"

#include "Polynomial/interpolate.hpp"

using mint = modint998244353;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    vector<mint> x(n), y(n);
    for (auto &i : x)
        cin >> i;
    for (auto &i : y)
        cin >> i;
    auto res = interpolate(x, y);
    for (int i = 0; i < n; ++i)
        cout << res[i] << " \n"[i + 1 == n];
}
