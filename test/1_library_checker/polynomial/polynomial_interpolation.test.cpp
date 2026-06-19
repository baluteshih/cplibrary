#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_interpolation"
#include "assumption.hpp"

#include "Polynomial/interpolate.hpp"

using mint = modint998244353;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n;
    std::cin >> n;
    std::vector<mint> x(n), y(n);
    for (auto &i : x)
        std::cin >> i;
    for (auto &i : y)
        std::cin >> i;
    auto res = interpolate(x, y);
    for (int i = 0; i < n; ++i)
        std::cout << res[i] << " \n"[i + 1 == n];
}
