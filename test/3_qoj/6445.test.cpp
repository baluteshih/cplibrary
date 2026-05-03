#define PROBLEM "https://qoj.ac/problem/6445"
#define IGNORE
#include "default_code.hpp"

#include "Geometry/convexHull3D.hpp"
#include "Geometry/minimum_enclosing_circle.hpp"

using Point3 = Pt3<ll>;
using Point = Pt<double>; 

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    vector<Point3> arr(n);
    for (auto &p : arr)
        cin >> p;
    auto res = convexHull3D(arr);
    double ans = 1e18;
    for (auto &f : res.res) {
        vector<Point> pts;
        double height = 0;
        for (auto &p : arr) {
            chmax(height, res.get_dis(p, f));
            pts.push_back(proj(res.P[f.a], res.P[f.b], res.P[f.c], p));
        }
        double r = minimum_enclosing_circle(pts).r;
        chmin(ans, height * r * r * numbers::pi);
    }
    cout << fixed << setprecision(8) << ans << "\n";
}
