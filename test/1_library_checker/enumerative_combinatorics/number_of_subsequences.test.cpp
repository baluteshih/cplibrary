#define PROBLEM "https://judge.yosupo.jp/problem/number_of_subsequences"
#include "assumption.hpp"

#include "Sequence/same_position.hpp"
#include "Numeric/Modint.hpp"

using mint = modint998244353;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (auto &i : arr)
        std::cin >> i;
    std::vector<mint> dp(n + 1);
    dp[0] = 1;
    auto prv = previous_same_position(arr);
    for (int i = 1; i <= n; ++i) {
        dp[i] = dp[i - 1];
        if (prv[i - 1] != -1) dp[i] -= dp[prv[i - 1]];
        dp[i] += dp[i - 1];
    }
    std::cout << dp.back() - 1 << "\n";
}
