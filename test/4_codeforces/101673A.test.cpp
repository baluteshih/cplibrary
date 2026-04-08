#define PROBLEM "https://codeforces.com/gym/101673/problem/A"
#define IGNORE
#include "default_code.hpp"

#include "Geometry/polygon.hpp"

using Point = Pt<int>;
using polygon = Polygon<int>;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n;
    ll area = 0;
    cin >> n;
    vector<polygon> poly(n);
    for (auto &p : poly) {
        int m;
        cin >> m;
        p.resize(m);
        for (auto &pt : p)
            cin >> pt;
        if (p.area() < 0)
            ranges::reverse(p);
        area += p.area();
    }
    cout << fixed << setprecision(8) << (double)area / 2 << " " << polyUnionArea(poly) << "\n";
}
