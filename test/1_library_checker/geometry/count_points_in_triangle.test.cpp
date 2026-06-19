#define PROBLEM "https://judge.yosupo.jp/problem/count_points_in_triangle"
#include "assumption.hpp"

#include "Geometry/PointInAngle.hpp"

using Point = Pt<long long>;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, m, q;
    std::cin >> n;
    std::vector<Point> arr(n);
    for (auto &p : arr)
        std::cin >> p;
    std::cin >> m;
    std::vector<Point> extra(m);
    for (auto &p : extra)
        std::cin >> p;
    PointInAngle<int, Point> ds(arr, std::vector<int>(n, 0), extra, std::vector<int>(m, 1));
    std::cin >> q;
    while (q--) {
        int x, y, z;
        std::cin >> x >> y >> z;
        std::cout << ds.calc_tri(x, y, z) << "\n";
    }
}
