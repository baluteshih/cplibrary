#define PROBLEM "https://qoj.ac/problem/6445"
#define IGNORE
#include "assumption.hpp"

#include "Geometry/convexHull3D.hpp"
#include "Geometry/minimum_enclosing_circle.hpp"

using Point3 = Pt3<long long>;
using Point = Pt<double>; 

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n;
    std::cin >> n;
    std::vector<Point3> arr(n);
    for (auto &p : arr)
        std::cin >> p;
    auto res = convexHull3D(arr);
    double ans = 1e18;
    for (auto &f : res.res) {
        std::vector<Point> pts;
        double height = 0;
        for (auto &p : arr) {
            height = std::max(height, res.get_dis(p, f));
            pts.push_back(proj(res.P[f.a], res.P[f.b], res.P[f.c], p));
        }
        double r = minimum_enclosing_circle(pts).r;
        ans = std::min(ans, height * r * r * std::numbers::pi);
    }
    std::cout << std::fixed << std::setprecision(8) << ans << "\n";
}
