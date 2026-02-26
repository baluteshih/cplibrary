#define PROBLEM "https://judge.yosupo.jp/problem/multipoint_evaluation"
#include "default_code.hpp"

#include "Polynomial/Polynomial.hpp"
#include "Numeric/Modint.hpp"

using mint = modint998244353;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    Poly_t poly(n);
    for (auto &i : poly)
        cin >> i;
    vector<mint> arr(m);
    for (auto &i : arr)
        cin >> i;
    auto res = poly.Eval(arr);
    for (int i = 0; i < m; ++i)
        cout << res[i] << " \n"[i + 1 == m];
}
