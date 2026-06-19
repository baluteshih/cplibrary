#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_of_formal_power_series"
#include "assumption.hpp"

#include "Polynomial/Sqrt.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n;
    std::cin >> n;
    Poly_t a(n);
    for (auto &i : a)
        std::cin >> i;
    if (!a.has_sqrt())
        std::cout << "-1\n";
    else {
        a = a.Sqrt();
        for (int i = 0; i < int(a.size()); ++i)
            std::cout << a[i] << " \n"[i + 1 == int(a.size())];
    }
}
