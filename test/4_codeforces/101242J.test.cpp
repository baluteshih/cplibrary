#define PROBLEM "https://codeforces.com/gym/101242/problem/J"
#define IGNORE
#include "assumption.hpp"

#include "Geometry/convex.hpp"

using Point = Pt<long long>;
using polygon = Polygon<long long>;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, num_one = 0;
    std::cin >> n;
    std::vector<Point> zero;
    std::set<Point> one;
    for (int i = 0; i < n; ++i) {
        int a, b, c;
        std::cin >> a >> b >> c;
        if (c == 0) zero.emplace_back(a, b);
        else ++num_one, one.emplace(a, b);
    }
    auto convex = convexHull(std::vector<Point>(one.begin(), one.end()));
    if (int(convex.size()) == 1) {
        if (num_one == 1) std::cout << "1\n";
        else {
            int ans = num_one;
            for (auto p : zero)
                if (p == convex[0])
                    ++ans;
            std::cout << ans << "\n";
        }
        return 0;
    }
    if (int(convex.size()) == 2) {
        int ans = num_one;
        for (auto p : zero)
            if (pointOnSeg(p, Ln(convex[0], convex[1])))
                ++ans;
        std::cout << ans << "\n";
        return 0;
    }
    std::vector<Point> vec, nzero;
    std::vector<std::pair<int, int>> tangent;
    for (int i = 0; i < int(zero.size()); ++i) {
        if (pointInConvex(zero[i], convex) >= 0) {
            ++num_one;
            continue;
        }
        int cur = nzero.size();
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
    std::ranges::sort(vec, cmp);
    vec.erase(std::ranges::unique(vec, [&](auto a, auto b) {
        return sameDirection(a, b);
    }).begin(), vec.end());
    std::vector<std::pair<int, int>> itv;
    auto add_itv = [&](int l, int r) {
        itv.emplace_back(l, 1);  
        itv.emplace_back(r, -1);  
    };
    int ans = n, flag = 0;
    for (int i = 0; i < int(nzero.size()); ++i) {
        Point a = convex[tangent[i].first];
        Point b = convex[tangent[i].second];
        Point p = nzero[i];
        assert(side(p, a, b) >= 0);
        {
            int r = std::ranges::lower_bound(vec, b - p, cmp) - vec.begin();
            int l = std::ranges::lower_bound(vec, a - p, cmp) - vec.begin();
            if (l <= r) add_itv(l, r);
            else add_itv(0, r), add_itv(l, int(vec.size()) - 1), flag = 1;
        }
        {
            int r = std::ranges::lower_bound(vec, p - b, cmp) - vec.begin();
            int l = std::ranges::lower_bound(vec, p - a, cmp) - vec.begin();
            if (l <= r) add_itv(l, r);
            else add_itv(0, r), add_itv(l, int(vec.size()) - 1), flag = 1;
        }
    }
    if (int(itv.size()) > 1 && flag) {
        std::ranges::sort(itv);
        int cur = 0;
        for (int i = 0; i < int(itv.size()) - 1; ++i) {
            cur += itv[i].second;
            if (itv[i].first != itv[i + 1].first) ans = std::min(ans, cur + num_one);
        }
    }
    else    
        ans = num_one;
    std::cout << ans << "\n";
}
