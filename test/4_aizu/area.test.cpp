#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_A"
#include "default_code.hpp"

#include "Geometry/Polygon.hpp"

using polygon = Polygon<int>;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    polygon poly(n);
    for (auto &p : poly)
        cin >> p;
    int res = poly.area();
    if (res % 2 == 0) cout << res / 2 << ".0\n";
    else cout << res / 2 << ".5\n";
}
