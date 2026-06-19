#define PROBLEM "https://judge.yosupo.jp/problem/partition_function"
#include "assumption.hpp"

#include "Numeric/Modint.hpp"
#include "Numbers/partition_number.hpp"

using mint = modint998244353;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n;
    std::cin >> n;
    auto res = partition_number<mint>(n);
    for (int i = 0; i <= n; ++i)
        std::cout << res[i] << " \n"[i == n];
}
