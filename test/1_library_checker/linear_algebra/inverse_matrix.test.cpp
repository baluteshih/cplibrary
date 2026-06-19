#define PROBLEM "https://judge.yosupo.jp/problem/inverse_matrix"
#include "assumption.hpp"

#include "Numeric/Modint.hpp"

#include "Matrix/Matrix.hpp"

using mint = modint998244353;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n;
    std::cin >> n;
    Matrix<mint> A(n);
    for (auto &row : A)
        for (auto &v : row)
            std::cin >> v;
    auto [det, iA] = A.inv();
    if (det == mint(0)) std::cout << "-1\n";
    else
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                std::cout << iA[i][j] << " \n"[j + 1 == n];
}
