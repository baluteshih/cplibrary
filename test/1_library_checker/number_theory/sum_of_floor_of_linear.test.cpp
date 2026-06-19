#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_floor_of_linear"
#include "assumption.hpp"

#include "Numeric/floor_sum.hpp"

void solve() {
    long long n, m, a, b;
    std::cin >> n >> m >> a >> b;
    std::cout << floor_sum(n, m, a, b) << "\n";
}

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
}
