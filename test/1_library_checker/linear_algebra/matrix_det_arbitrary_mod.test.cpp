#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det_arbitrary_mod"
#include "default_code.hpp"

#include "Numeric/Modint.hpp"

#include "Matrix/Matrix.hpp"

using mint = modint;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    modint::set_mod(m);
    Matrix<mint> A(n);
    for (auto &row : A)
        for (auto &v : row)
            cin >> v;
    auto res = A.det<Matrix<mint>::gauss_mode::euclidean>();
    cout << res << "\n";
}
