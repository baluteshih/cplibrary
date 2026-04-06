#pragma once

#include "Geometry/convex.hpp"
#include "Misc/cyc_bitonic_search.hpp"

template<typename Point>
std::pair<int, int> furthest_pair(const std::vector<Point> &dots) {
    int n = dots.size();
    assert(n >= 2);
    auto convex = convexHull(dots);
    if (SZ(convex) == 1) return std::make_pair(0, 1);
    auto res = rotating_calipers(SZ(convex), [&](int o, int a, int b) {
        return Point::cmp(cross(convex[o], convex[(o + 1) % SZ(convex)], convex[a]), cross(convex[o], convex[(o + 1) % SZ(convex)], convex[b])) > 0; 
    });
    std::pair<int, int> ans = std::make_pair(0, res[0]);
    for (int i = 1; i < SZ(convex); ++i)
        if (dist2(convex[ans.first], convex[ans.second]) < dist2(convex[i], convex[res[i]]))
            ans = std::make_pair(i, res[i]);
    return std::make_pair(ranges::find(dots, convex[ans.first]) - dots.begin(), ranges::find(dots, convex[ans.second]) - dots.begin());
}
