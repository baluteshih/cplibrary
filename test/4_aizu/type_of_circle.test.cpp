#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_A"
#include "default_code.hpp"

#include "Geometry/circle.hpp"

using cir = Circle<int>;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cir a, b;
    cin >> a.o >> a.r >> b.o >> b.r;
    cout << typeOfCircles(a, b) << "\n";
}
