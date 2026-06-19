#define PROBLEM "https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence"
#include "assumption.hpp"

#include "Polynomial/linear_recursion.hpp"

using mint = modint998244353;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n;
    long long m;
    std::cin >> n >> m;
    std::vector<mint> a(n), coef(n);
    for (auto &i : a)
        std::cin >> i;
    for (auto &i : coef)
        std::cin >> i;
    std::cout << linear_recursion(a, coef, m) << "\n";
}

