#define PROBLEM "https://qoj.ac/contest/782/problem/2162"
#define IGNORE
#include "assumption.hpp"

#include "Geometry/half_plane_intersection.hpp"
#include "Geometry/polygon.hpp"
#include "Geometry/convex.hpp"

using Point = Pt<long long>;
using Line = Ln<long long>;
using polygon = Polygon<double>;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int dx, dy, n;
    std::cin >> dx >> dy >> n;
    std::vector<Point> dots(n);
    for (auto &p : dots)
        std::cin >> p;
    std::vector<int> perm(n), pl(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> perm[i];
        --perm[i];
        pl[perm[i]] = i;
    }
    std::cout << std::fixed << std::setprecision(6);
    if (n == 1) {
        std::cout << (double)dx * dy << "\n";
        return 0;
    }
    std::vector<Line> lines;
    lines.push_back(Line(Point(0, 0), Point(dx, 0)));
    lines.push_back(Line(Point(dx, 0), Point(dx, dy)));
    lines.push_back(Line(Point(dx, dy), Point(0, dy)));
    lines.push_back(Line(Point(0, dy), Point(0, 0)));
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j) {
            if (pl[i] > pl[j])
                lines.push_back(Line(dots[i], dots[j]));
            else
                lines.push_back(Line(dots[j], dots[i]));
        }

    auto area = [&](const std::vector<Line> &ln) {
        if (int(ln.size()) <= 2) return (double)0;
        polygon poly;
        for (int i = 0; i < int(ln.size()); ++i)
            poly.push_back(lineIntersection(ln[i], ln[(i + 1) % int(ln.size())]));
        return poly.area();
    };

    auto res = half_plane_intersection<Line, __int128>(lines);
    double ans = area(res);
    auto convex = convexHull(dots); 
    for (int i = 0; i < int(convex.size()); ++i)
        lines.push_back(Line(convex[i], convex[(i + 1) % int(convex.size())]));
    res = half_plane_intersection<Line, __int128>(lines);
    ans -= area(res);
    std::cout << ans / 2 << "\n";
}
