#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_B"
#define ERROR 0.000001
#include "assumption.hpp"

#include "Geometry/centers.hpp"

using Point = Pt<int>;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    Point a, b, c;
    std::cin >> a >> b >> c;
    auto ans = incenter(a, b, c);
    std::cout << std::fixed << std::setprecision(20);
    std::cout << ans << " " << pointToLineDist(ans, LineType<decltype(ans)>::type(a, b)) << "\n";
}

