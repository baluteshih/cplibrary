#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product"
#include "assumption.hpp"

#include "Numeric/Modint.hpp"

#include "Matrix/Matrix.hpp"

using mint = modint998244353;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, m, k;
    std::cin >> n >> m >> k;
    Matrix<mint> A(n, m), B(m, k);
    for (auto &row : A)
        for (auto &v : row)
            std::cin >> v;
    for (auto &row : B)
        for (auto &v : row)
            std::cin >> v;
    A = A * B;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < k; ++j)
            std::cout << A[i][j] << " \n"[j + 1 == k];
}
