#define PROBLEM "https://judge.yosupo.jp/problem/find_linear_recurrence"
#include "assumption.hpp"

#include "Numeric/berlekamp_massey.hpp"
#include "Numeric/Modint.hpp"

using mint = modint998244353;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n;
    std::cin >> n;
    std::vector<mint> arr(n);
    for (mint &i : arr) std::cin >> i;
    auto ans = berlekamp_massey(arr);
    std::cout << ans.size() << "\n";
    for (int i = 0; i < int(ans.size()); ++i)
        std::cout << ans[i] << " \n"[i + 1 == int(ans.size())];
}
