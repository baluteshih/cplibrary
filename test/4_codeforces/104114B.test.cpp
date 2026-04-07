#define PROBLEM "https://codeforces.com/gym/104114/problem/B"
#define IGNORE
#include "default_code.hpp"

#include "Geometry/convex.hpp"

using Point = Pt<ll>;
using polygon = Polygon<ll>;

const int MAXC = 1000000;

struct Event {
    Point vec;
    int v;
};

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<Point> arr(n);
    for (auto &p : arr) {
        double x, y;
        cin >> x >> y;
        p = Point(round(x * MAXC), round(y * MAXC));
    }
    vector<Point> brr(m);
    for (auto &p : brr) {
        double x, y;
        cin >> x >> y;
        p = Point(round(x * MAXC), round(y * MAXC));
    }
    auto convex = convexHull(brr);
    vector<Event> event;
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
    ranges::sort(event, [&](auto &a, auto &b) {
        return polar(a.vec, b.vec);
    });
    int ans = cur;
    for (int i = 0, j = 0; i < SZ(event); i = j) {
        while (j < SZ(event) && sameDirection(event[i].vec, event[j].vec))
            cur += event[j].v, ++j;
        ans = max(ans, cur);
    }
    cout << ans << "\n";
}
