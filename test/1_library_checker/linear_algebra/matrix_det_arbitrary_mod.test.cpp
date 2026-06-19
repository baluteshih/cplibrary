#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det_arbitrary_mod"
#include "assumption.hpp"

#include "Numeric/DynamicModint.hpp"
#include "Matrix/Matrix.hpp"

using mint = modint;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    modint::set_mod(m);
    Matrix<mint> A(n);
    for (auto &row : A)
        for (auto &v : row)
            std::cin >> v;
    auto res = A.det<Matrix<mint>::gauss_mode::euclidean>();
    std::cout << res << "\n";
}
