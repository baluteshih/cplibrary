#define PROBLEM "https://judge.yosupo.jp/problem/sort_points_by_argument"
#include "default_code.hpp"

#include "Geometry/base.hpp"

using Point = Pt<ll>;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    vector<Point> dots(n);
    for (auto &p : dots)
        cin >> p;
    int zero_count = 0;
    {
        vector<Point> swp;
        for (auto &p : dots)
            if (p != Point()) swp.push_back(p);
            else ++zero_count;
        dots.swap(swp);
    }
    ranges::sort(dots, [](const auto &a, const auto &b) {
        return polar(a, b);   
    });
    ranges::rotate(dots, ranges::min_element(dots, [](const auto &a, const auto &b) {
        if (sameDirection(Point(-1, 0), a)) return false;
        if (sameDirection(Point(-1, 0), b)) return true;
        return polar(a, b, Point(-1, 0)); 
    }));
    dots.insert(ranges::min_element(dots, [](const auto &a, const auto &b) {
        return polar(a, b, Point(1, 0)); 
    }), zero_count, Point());
    for (auto &p : dots)
        cout << p << "\n";
}
