#define PROBLEM "https://judge.yosupo.jp/problem/system_of_linear_equations"
#include "default_code.hpp"

#include "Numeric/Modint.hpp"

#include "Matrix/Matrix.hpp"

using mint = modint998244353;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    Matrix<mint> A(n, m);
    for (auto &row : A)
        for (auto &v : row)
            cin >> v;
    Vector<mint> b(n);
    for (auto &x : b)
        cin >> x;
    auto x = A.solve(b);
    if (!x) cout << "-1\n";
    else {
        auto [sol, basis] = *x;
        cout << basis.n() << "\n";
        for (int i = 0; i < sol.m(); ++i)
            cout << sol[0][i] << " \n"[i + 1 == sol.m()];
        for (int i = 0; i < basis.n(); ++i)
            for (int j = 0; j < basis.m(); ++j)
                cout << basis[i][j] << " \n"[j + 1 == basis.m()];
    }
}
