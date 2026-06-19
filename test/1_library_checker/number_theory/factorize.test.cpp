#define PROBLEM "https://judge.yosupo.jp/problem/factorize"
#include "default_code.hpp"

#include "Numeric/pollard_rho.hpp"

int main() {
    ios::sync_with_stdio(0), std::cin.tie(0);
    int q;
    std::cin >> q;
    while (q--) {
        long long x;
        std::cin >> x;
        std::vector<long long> ans = pollard_rho(x);
        std::ranges::sort(ans);
        std::cout << SZ(ans);
        for (long long i : ans)
            std::cout << " " << i;
        std::cout << "\n";
    }
}
