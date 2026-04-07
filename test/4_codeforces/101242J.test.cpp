#define PROBLEM "https://codeforces.com/gym/101242/problem/J"
#define IGNORE
#include "default_code.hpp"

#include "Geometry/convex.hpp"

using Point = Pt<ll>;
using polygon = Polygon<ll>;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, num_one = 0;
    cin >> n;
    vector<Point> zero;
    set<Point> one;
    for (int i = 0; i < n; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        if (c == 0) zero.emplace_back(a, b);
        else ++num_one, one.emplace(a, b);
    }
    auto convex = convexHull(vector<Point>(ALL(one)));
    if (SZ(convex) == 1) {
        if (num_one == 1) cout << "1\n";
        else {
            int ans = num_one;
            for (auto p : zero)
                if (p == convex[0])
                    ++ans;
            cout << ans << "\n";
        }
        return 0;
    }
    if (SZ(convex) == 2) {
        int ans = num_one;
        for (auto p : zero)
            if (pointOnSeg(p, Ln(convex[0], convex[1])))
                ++ans;
        cout << ans << "\n";
        return 0;
    }
    vector<Point> vec, nzero;
    vector<pii> tangent;
    for (int i = 0; i < SZ(zero); ++i) {
        if (pointInConvex(zero[i], convex) >= 0) {
            ++num_one;
            continue;
        }
        int cur = SZ(nzero);
        tangent.push_back(tangentLineToConvex(zero[i], convex));
        vec.push_back(convex[tangent[cur].first] - zero[i]);
        vec.push_back(convex[tangent[cur].second] - zero[i]);
        vec.push_back(zero[i] - convex[tangent[cur].first]);
        vec.push_back(zero[i] - convex[tangent[cur].second]);
        nzero.push_back(zero[i]);
    }
    auto cmp = [&](auto a, auto b) {
        return polar(a, b);  
    };
    ranges::sort(vec, cmp);
    vec.erase(ranges::unique(vec, [&](auto a, auto b) {
        return sameDirection(a, b);
    }).begin(), vec.end());
    vector<pii> itv;
    auto add_itv = [&](int l, int r) {
        itv.emplace_back(l, 1);  
        itv.emplace_back(r, -1);  
    };
    int ans = n, flag = 0;
    for (int i = 0; i < SZ(nzero); ++i) {
        Point a = convex[tangent[i].first];
        Point b = convex[tangent[i].second];
        Point p = nzero[i];
        assert(side(p, a, b) >= 0);
        {
            int r = ranges::lower_bound(vec, b - p, cmp) - vec.begin();
            int l = ranges::lower_bound(vec, a - p, cmp) - vec.begin();
            if (l <= r) add_itv(l, r);
            else add_itv(0, r), add_itv(l, SZ(vec) - 1), flag = 1;
        }
        {
            int r = ranges::lower_bound(vec, p - b, cmp) - vec.begin();
            int l = ranges::lower_bound(vec, p - a, cmp) - vec.begin();
            if (l <= r) add_itv(l, r);
            else add_itv(0, r), add_itv(l, SZ(vec) - 1), flag = 1;
        }
    }
    if (SZ(itv) > 1 && flag) {
        ranges::sort(itv);
        int cur = 0;
        for (int i = 0; i < SZ(itv) - 1; ++i) {
            cur += itv[i].Y;
            if (itv[i].X != itv[i + 1].X) ans = min(ans, cur + num_one);
        }
    }
    else    
        ans = num_one;
    cout << ans << "\n";
}
