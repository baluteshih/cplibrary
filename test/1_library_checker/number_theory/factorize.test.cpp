#define PROBLEM "https://judge.yosupo.jp/problem/factorize"
#include "assumption.hpp"

#include "Numeric/pollard_rho.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int q;
    std::cin >> q;
    while (q--) {
        long long x;
        std::cin >> x;
        std::vector<long long> ans = pollard_rho(x);
        std::ranges::sort(ans);
        std::cout << ans.size();
        for (long long i : ans)
            std::cout << " " << i;
        std::cout << "\n";
    }
}
