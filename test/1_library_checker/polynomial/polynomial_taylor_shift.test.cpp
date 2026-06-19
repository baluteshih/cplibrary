#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_taylor_shift"
#include "assumption.hpp"

#include "Polynomial/shift.hpp"

using mint = modint998244353;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n;
    mint c;
    std::cin >> n >> c;
    Poly_t a(n);
    for (auto &i : a)
        std::cin >> i;
    a.shift(c);
    for (int i = 0; i < n; ++i)
        std::cout << a[i] << " \n"[i + 1 == n]; 
}
