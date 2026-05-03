#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_5_B"
#define ERROR 0.000001
#include "default_code.hpp"

#include "Geometry/minimum_enclosing_circle.hpp"

using Point = Pt<int>;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    vector<Point> arr(n);
    for (auto &p : arr)
        cin >> p;
    auto [o, r] = minimum_enclosing_circle(arr);
    cout << fixed << setprecision(8) << o << " " << r << "\n";
}
