#define PROBLEM "https://judge.yosupo.jp/problem/matrix_rank"
#include "assumption.hpp"

#include "Numeric/Modint.hpp"

#include "Matrix/Matrix.hpp"

using mint = modint998244353;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    Matrix<mint> A(n, m);
    for (auto &row : A)
        for (auto &v : row)
            std::cin >> v;
    std::cout << A.rank() << "\n";
}
