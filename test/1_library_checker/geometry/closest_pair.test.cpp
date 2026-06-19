#define PROBLEM "https://judge.yosupo.jp/problem/closest_pair"
#include "assumption.hpp"

#include "Geometry/closest_pair.hpp"

using Point = Pt<long long>;

void solve() {
    int n;
    std::cin >> n;
    std::vector<Point> arr(n);
    for (auto &p : arr)
        std::cin >> p;
    auto [i, j] = closest_pair(arr);
    std::cout << i << " " << j << "\n";
}

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
}
