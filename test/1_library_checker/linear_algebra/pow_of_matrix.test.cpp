#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_matrix"
#include "default_code.hpp"

#include "Numeric/Modint.hpp"

#include "Matrix/Matrix.hpp"

using mint = modint998244353;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n;
    ll k;
    std::cin >> n >> k;
    Matrix<mint> A(n);
    for (auto &row : A)
        for (auto &v : row)
            cin >> v;
    auto res = A.pow(k);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cout << res[i][j] << " \n"[j + 1 == n];
}
