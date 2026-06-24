#define PROBLEM "https://judge.yosupo.jp/problem/stirling_first_kind"
#include "assumption.hpp"

#include "Numeric/Modint.hpp"
#include "Numbers/stirling_first_kind.hpp"

using mint = modint998244353;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n;
    std::cin >> n;
    auto res = stirling_first_kind<mint>(n);
    for (int i = 0; i <= n; ++i)
        std::cout << res[i] << " \n"[i == n];
}
