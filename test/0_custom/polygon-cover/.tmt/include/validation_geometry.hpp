#pragma once
#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>
struct Point { long long x, y; };
__int128 turn(Point a, Point b, Point c) {
    return __int128(b.x - a.x) * (c.y - a.y) - __int128(b.y - a.y) * (c.x - a.x);
}
bool on_segment(Point a, Point b, Point p) {
    return turn(a,b,p) == 0 && std::min(a.x,b.x) <= p.x && p.x <= std::max(a.x,b.x)
        && std::min(a.y,b.y) <= p.y && p.y <= std::max(a.y,b.y);
}
bool intersects(Point a, Point b, Point c, Point d) {
    auto u = turn(a,b,c), v = turn(a,b,d), w = turn(c,d,a), z = turn(c,d,b);
    if (u == 0 && on_segment(a,b,c)) return true;
    if (v == 0 && on_segment(a,b,d)) return true;
    if (w == 0 && on_segment(c,d,a)) return true;
    if (z == 0 && on_segment(c,d,b)) return true;
    return (u > 0) != (v > 0) && (w > 0) != (z > 0) && u != 0 && v != 0 && w != 0 && z != 0;
}
bool simple_polygon(const std::vector<Point> &p) {
    int n = int(p.size());
    std::set<std::pair<long long,long long>> distinct;
    __int128 area = 0;
    for (int i = 0; i < n; ++i) {
        if (!distinct.emplace(p[i].x,p[i].y).second) return false;
        auto a = p[(i+n-1)%n], b = p[i], c = p[(i+1)%n];
        if (turn(a,b,c) == 0 && __int128(a.x-b.x)*(c.x-b.x)+__int128(a.y-b.y)*(c.y-b.y) > 0) return false;
        area += __int128(b.x)*c.y-__int128(b.y)*c.x;
    }
    if (area == 0) return false;
    std::vector<int> order(n), active;
    std::iota(order.begin(),order.end(),0);
    auto low = [&](int i) { return std::min(p[i].x,p[(i+1)%n].x); };
    auto high = [&](int i) { return std::max(p[i].x,p[(i+1)%n].x); };
    std::sort(order.begin(),order.end(),[&](int a,int b) { return low(a)<low(b); });
    for (int i : order) {
        auto a = p[i], b = p[(i+1)%n];
        active.erase(std::remove_if(active.begin(),active.end(),[&](int j) { return high(j)<low(i); }),active.end());
        for (int j : active) {
            if ((i+1)%n == j || (j+1)%n == i) continue;
            auto c = p[j], d = p[(j+1)%n];
            if (std::max(a.y,b.y)<std::min(c.y,d.y) || std::max(c.y,d.y)<std::min(a.y,b.y)) continue;
            if (intersects(a,b,c,d)) return false;
        }
        active.push_back(i);
    }
    return true;
}
