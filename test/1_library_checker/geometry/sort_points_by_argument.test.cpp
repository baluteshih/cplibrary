#define PROBLEM "https://judge.yosupo.jp/problem/sort_points_by_argument"
#include "assumption.hpp"

#include "Geometry/base.hpp"

using Point = Pt<long long>;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n;
    std::cin >> n;
    std::vector<Point> dots(n);
    for (auto &p : dots)
        std::cin >> p;
    int zero_count = 0;
    {
        std::vector<Point> swp;
        for (auto &p : dots)
            if (p != Point()) swp.push_back(p);
            else ++zero_count;
        dots.swap(swp);
    }
    std::ranges::sort(dots, [](const auto &a, const auto &b) {
        return polar(a, b);   
    });
    std::ranges::rotate(dots, std::ranges::min_element(dots, [](const auto &a, const auto &b) {
        if (sameDirection(Point(-1, 0), a)) return false;
        if (sameDirection(Point(-1, 0), b)) return true;
        return polar(a, b, Point(-1, 0)); 
    }));
    dots.insert(std::ranges::min_element(dots, [](const auto &a, const auto &b) {
        return polar(a, b, Point(1, 0)); 
    }), zero_count, Point());
    for (auto &p : dots)
        std::cout << p << "\n";
}
