#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_quotients"
#include "assumption.hpp"

#include "Numeric/floor_enumerate.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    long long n;
    std::cin >> n;
    std::vector<long long> ans;
    floor_enumerate(n, [&](long long x, [[maybe_unused]] long long l, [[maybe_unused]] long long r) {
        ans.push_back(x); 
    });
    std::ranges::reverse(ans);
    std::cout << ans.size() << "\n";
    for (int i = 0; i < int(ans.size()); ++i)
        std::cout << ans[i] << " \n"[i + 1 == int(ans.size())];
}
