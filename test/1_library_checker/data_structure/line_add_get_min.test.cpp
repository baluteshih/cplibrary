#define PROBLEM "https://judge.yosupo.jp/problem/line_add_get_min"
#include "assumption.hpp"

#include "DataStructure/Convex/DynamicHull.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    DynamicHull<long long> hull;
    for (int i = 0; i < n; ++i) {
        long long a, b;
        std::cin >> a >> b;
        hull.addline(-a, -b);
    }
    while (q--) {
        int type;
        std::cin >> type;
        if (type == 0) {
            long long a, b;
            std::cin >> a >> b;
            hull.addline(-a, -b);
        }
        else {
            long long p;
            std::cin >> p;
            std::cout << -hull.query(p) << "\n";
        }
    }
}
