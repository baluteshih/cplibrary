#define PROBLEM "https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod"
#include "assumption.hpp"

#include "Numeric/Combination.hpp"
#include "Numeric/DynamicModint.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int t, m;
    std::cin >> t >> m;
    modint v;
    v.set_mod(m);
    Combination<modint> comb(std::min(10000000, m), v);
    while (t--) {
        int n, k;
        std::cin >> n >> k;
        std::cout << comb.C(n, k) << "\n";
    }
}
