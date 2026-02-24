#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det"
#include "default_code.hpp"

#include "Numeric/Modint.hpp"

#include "Matrix/Matrix.hpp"

using mint = modint998244353;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n;
    std::cin >> n;
    Matrix<mint> A(n);
    for (auto &row : A)
        for (auto &v : row)
            cin >> v;
    cout << A.det() << "\n";
}
