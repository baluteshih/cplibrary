#define PROBLEM "https://judge.yosupo.jp/problem/binomial_coefficient"
#include "assumption.hpp"

#include "Numeric/Binomial.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int t, m;
    std::cin >> t >> m;
    Binomial binom(m);
    while (t--) {
        long long n, k;
        std::cin >> n >> k;
        std::cout << binom.C(n, k) << "\n";
    }
}
