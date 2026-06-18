#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_A"
#include <bits/stdc++.h>
#include <cassert>

#include "Geometry/polygon.hpp"

using polygon = Polygon<int>;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n;
    std::cin >> n;
    polygon poly(n);
    for (auto &p : poly)
        std::cin >> p;
    int res = poly.area();
    if (res % 2 == 0) std::cout << res / 2 << ".0\n";
    else std::cout << res / 2 << ".5\n";
}
