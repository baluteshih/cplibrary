#define PROBLEM "https://codeforces.com/gym/104114/problem/B"
#define IGNORE
#include "assumption.hpp"

#include "Geometry/convex.hpp"

using Point = Pt<long long>;
using polygon = Polygon<long long>;

const int MAXC = 1000000;

struct Event {
    Point vec;
    int v;
};

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    std::vector<Point> arr(n);
    for (auto &p : arr) {
        double x, y;
        std::cin >> x >> y;
        p = Point(std::round(x * MAXC), std::round(y * MAXC));
    }
    std::vector<Point> brr(m);
    for (auto &p : brr) {
        double x, y;
        std::cin >> x >> y;
        p = Point(std::round(x * MAXC), std::round(y * MAXC));
    }
    auto convex = convexHull(brr);
    std::vector<Event> event;
    int cur = 0;
    for (int i = 0; i < n; ++i) {
        if (pointInConvex(arr[i], convex) >= 0) continue;
        auto [r, l] = tangentLineToConvex(arr[i], convex);
        assert(side(arr[i], convex[r], convex[l]) >= 0);
        Point lft = arr[i] - convex[l];
        Point rgt = convex[r] - arr[i];
        if (betweenAngle(Point(0, 0), lft, rgt, Point(1, 0), 1))
            ++cur;
        else if (rgt.x > 0 && rgt.y == 0)
            ++cur;
        event.push_back(Event{lft, 1});
        event.push_back(Event{rgt, -1});
    }
    std::ranges::sort(event, [&](auto &a, auto &b) {
        return polar(a.vec, b.vec);
    });
    int ans = cur;
    for (int i = 0, j = 0; i < int(event.size()); i = j) {
        while (j < int(event.size()) && sameDirection(event[i].vec, event[j].vec))
            cur += event[j].v, ++j;
        ans = std::max(ans, cur);
    }
    std::cout << ans << "\n";
}
