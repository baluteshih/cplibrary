#define PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_second_kind_fixed_k"
#include "assumption.hpp"

#include "Numeric/Modint.hpp"
#include "Numbers/stirling_second_kind_row.hpp"

using mint = modint998244353;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, k;
    std::cin >> n >> k;
    auto res = stirling_second_kind_row<mint>(k, n);
    for (int i = k; i <= n; ++i)
        std::cout << res[i] << " \n"[i == n];
}
