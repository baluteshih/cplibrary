#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_G"
#include "default_code.hpp"

#include "Geometry/circle.hpp"

using cir = Circle<int>;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cir a, b;
    cin >> a.o >> a.r >> b.o >> b.r;
    vector<Pt<double>> ans;
    for (auto ln : externalTangent(a, b))
        ans.push_back(ln[0]);
    for (auto ln : internalTangent(a, b))
        ans.push_back(ln[0]);
    if (typeOfCircles(a, b) == 3)
        ans.push_back(Pt<double>(a.o * b.r + b.o * a.r) / (double)(a.r + b.r));
    if (typeOfCircles(a, b) == 1) {
        ans.push_back(Pt<double>(a.o * b.r - b.o * a.r) / (double)(b.r - a.r));
    }
    sort(ans.begin(), ans.end());
    cout << fixed << setprecision(10);
    for (auto p : ans)
        cout << p << "\n";
}

