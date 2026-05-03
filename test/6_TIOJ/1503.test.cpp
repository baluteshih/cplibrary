#define PROBLEM "https://tioj.ck.tp.edu.tw/problems/1503"
#define IGNORE 
#include "default_code.hpp"

#include "Geometry/circle_cover.hpp"

using Cir = Circle<int>;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, r;
    cin >> n >> r;
    vector<Cir> arr(n);
    for (auto &p : arr)
        cin >> p.o, p.r = r;
    cout << fixed << setprecision(2) << circle_cover(arr)[1] << "\n";
}
