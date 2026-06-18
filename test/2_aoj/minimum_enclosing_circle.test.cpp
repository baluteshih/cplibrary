#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_5_B"
#define ERROR 0.000001
#include "assumption.hpp"

#include "Geometry/minimum_enclosing_circle.hpp"

using Point = Pt<int>;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n;
    std::cin >> n;
    std::vector<Point> arr(n);
    for (auto &p : arr)
        std::cin >> p;
    auto [o, r] = minimum_enclosing_circle(arr);
    std::cout << std::fixed << std::setprecision(8) << o << " " << r << "\n";
}
