#define PROBLEM "https://yukicoder.me/problems/no/2114"
#include "assumption.hpp"

#include "DataStructure/Convex/ConjugateSlopeTrick.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, m, k;
    std::cin >> n >> m >> k;
    long long ans = 0;
    std::map<int, std::vector<std::pair<int, int>>> arr;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        arr[x % k].emplace_back(x / k, n > m);
    }
    for (int i = 0; i < m; ++i) {
        int x;
        std::cin >> x;
        arr[x % k].emplace_back(x / k, n <= m);
    }
    for (auto [_, vec] : arr) {
        std::ranges::sort(vec);
        int tot = 0;
        ConjugateSlopeTrick<long long> slope;
        for (int i = 0; i < int(vec.size()); ++i) {
            if (vec[i].second == 1) {
                ++tot;
                slope.convolve({0, 0});
            }
            else {
                --tot;
                slope.shift(-1);
            }
            if (i + 1 < int(vec.size()))
                slope.add_abs(vec[i + 1].first - vec[i].first);
        }
        if (tot < 0) return std::cout << "-1\n", 0;
        ans += slope.f0();
    }
    std::cout << ans << "\n";
}
