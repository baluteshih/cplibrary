#define PROBLEM "https://judge.yosupo.jp/problem/multipoint_evaluation"
#include "assumption.hpp"

#include "Polynomial/Polynomial.hpp"
#include "Numeric/Modint.hpp"

using mint = modint998244353;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    Poly_t poly(n);
    for (auto &i : poly)
        std::cin >> i;
    std::vector<mint> arr(m);
    for (auto &i : arr)
        std::cin >> i;
    auto res = poly.Eval(arr);
    for (int i = 0; i < m; ++i)
        std::cout << res[i] << " \n"[i + 1 == m];
}
