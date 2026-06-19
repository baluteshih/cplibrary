#define PROBLEM "https://judge.yosupo.jp/problem/shift_of_sampling_points_of_polynomial"
#include "assumption.hpp"

#include "Polynomial/lagrange_interpolate_iota.hpp"

using mint = modint998244353;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, m;
    mint c;
    std::cin >> n >> m >> c;
    Poly_t a(n);
    for (auto &i : a)
        std::cin >> i;
    auto res = lagrange_interpolate_iota(a, c, m);
    for (int i = 0; i < m; ++i)
        std::cout << res[i] << " \n"[i + 1 == m];
}
