#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_G"
#define ERROR 0.00001
#include "assumption.hpp"

#include "Geometry/circle.hpp"

using cir = Circle<int>;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    cir a, b;
    std::cin >> a.o >> a.r >> b.o >> b.r;
    std::vector<Pt<double>> ans;
    for (auto ln : externalTangent(a, b))
        ans.push_back(ln[0]);
    for (auto ln : internalTangent(a, b))
        ans.push_back(ln[0]);
    if (typeOfCircles(a, b) == 3)
        ans.push_back(Pt<double>(a.o * b.r + b.o * a.r) / (double)(a.r + b.r));
    if (typeOfCircles(a, b) == 1) {
        ans.push_back(Pt<double>(a.o * b.r - b.o * a.r) / (double)(b.r - a.r));
    }
    std::sort(ans.begin(), ans.end());
    std::cout << std::fixed << std::setprecision(10);
    for (auto p : ans)
        std::cout << p << "\n";
}

