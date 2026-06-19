#define PROBLEM "https://judge.yosupo.jp/problem/log_of_formal_power_series"
#include "assumption.hpp"

#include "Polynomial/Polynomial.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n;
    std::cin >> n;
    Poly_t a(n);
    for (auto &i : a)
        std::cin >> i;
    a = a.Ln();
    for (int i = 0; i < int(a.size()); ++i)
        std::cout << a[i] << " \n"[i + 1 == int(a.size())];
}
