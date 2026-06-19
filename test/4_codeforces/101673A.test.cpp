#define PROBLEM "https://codeforces.com/gym/101673/problem/A"
#define IGNORE
#include "assumption.hpp"

#include "Geometry/polygon.hpp"

using Point = Pt<int>;
using polygon = Polygon<int>;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n;
    long long area = 0;
    std::cin >> n;
    std::vector<polygon> poly(n);
    for (auto &p : poly) {
        int m;
        std::cin >> m;
        p.resize(m);
        for (auto &pt : p)
            std::cin >> pt;
        if (p.area() < 0)
            std::ranges::reverse(p);
        area += p.area();
    }
    std::cout << std::fixed << std::setprecision(8) << (double)area / 2 << " " << polyUnionArea(poly) << "\n";
}
