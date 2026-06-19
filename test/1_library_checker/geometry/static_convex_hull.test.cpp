#define PROBLEM "https://judge.yosupo.jp/problem/static_convex_hull"
#include "assumption.hpp"

#include "Geometry/convex.hpp"

using Point = Pt<long long>;

void solve() {
    int n;
    std::cin >> n;
    std::vector<Point> dots(n);
    for (auto &p : dots)
        std::cin >> p;
    auto hull = convexHull(dots);
    std::cout << hull.size() << "\n";
    for (auto p : hull)
        std::cout << p << "\n";
}

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
}
