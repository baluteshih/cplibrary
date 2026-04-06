#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_B"
#include "default_code.hpp"

#include "Geometry/centers.hpp"

using Point = Pt<int>;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    Point a, b, c;
    cin >> a >> b >> c;
    auto ans = incenter(a, b, c);
    cout << fixed << setprecision(20);
    cout << ans << " " << pointToLineDist(ans, LineType<decltype(ans)>::type(a, b)) << "\n";
}

