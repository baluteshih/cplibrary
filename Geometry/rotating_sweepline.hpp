#pragma once

#include "Geometry/base.hpp"

/*
init_order(const std::vector<int> &ord)

if reverse_convention is true:
update_ans(const std::vector<int> &ord, int l, int r): 
    calculate ans related to line(pts[ord[l]], pts[ord[l+1]], ..., pts[ord[r]]) with the support of ord
    ord[l..r] will be reversed after the call of update_ans, so if needed, update_ans should reverse the interval in their data structure  
else:
update_ans(const std::vector<int> &ord, int i): 
    calculate ans related to line(pts[ord[i]], pts[ord[i+1]]) with the support of ord
    ord[i], ord[i+1] will be swapped after the call of update_ans, so if needed, update_ans should swap the two elements in their data structure  
*/
template<typename Point, bool reverse_convention = true>
void rotating_sweepline(const std::vector<Point> &pts, auto init_order, auto update_ans, const Point &init = Point(1, 0)) {
    int n = pts.size();
    struct Event {
        Point dir; int u, v;
    };
    std::vector<Event> e; e.reserve(n * (n - 1));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (i != j)
                e.push_back({pts[j] - pts[i], i, j});
    std::ranges::sort(e.begin(), e.end(), [&](const Event &a, const Event &b) {
        return polar(a.dir, b.dir, init);
    });
    vector<int> ord(n), pos(n);
    std::iota(ord.begin(), ord.end(), 0);
    std::ranges::sort(ord, [&](int a, int b) {
        auto va = cross(init, pts[a]);
        auto vb = cross(init, pts[b]);
        if (va != vb) return va < vb;
        return dot(init, pts[a]) < dot(init, pts[b]);
    });
    for (int i = 0; i < n; i++) pos[ord[i]] = i;
    init_order(ord);
    for (int i = 0, j = 0; i < int(e.size()); i = j) {
        std::vector<std::pair<int, int>> tmp;
        for (; j < int(e.size()) && !polar(e[i].dir, e[j].dir, init); ++j)
            tmp.emplace_back(e[j].u, e[j].v);
        ranges::sort(tmp, [&](const std::pair<int, int> &x, const std::pair<int, int> &y) {
            return std::make_pair(pos[x.first], pos[x.second]) < std::make_pair(pos[y.first], pos[y.second]);
        });
        for (int k = 0; k < int(tmp.size()); ) {
            int l = pos[tmp[k].first], r = pos[tmp[k].second];
            for (int tk = k; tk < int(tmp.size()) && pos[tmp[tk].first] <= r; ++tk)
                r = std::max(r, pos[tmp[tk].second]);
            if constexpr (reverse_convention) update_ans(ord, l, r);
            for (; k < int(tmp.size()) && pos[tmp[k].first] <= r; ++k) {
                auto [x, y] = tmp[k]; 
                if constexpr (!reverse_convention) update_ans(ord, pos[x]);
                std::tie(ord[pos[x]], ord[pos[y]], pos[x], pos[y]) = std::make_tuple(ord[pos[y]], ord[pos[x]], pos[y], pos[x]);
            }
        }
    }
}
