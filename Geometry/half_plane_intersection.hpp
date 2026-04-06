#pragma once

#include "Geometry/base.hpp"
#include "Geometry/line.hpp"

// Check inter(l1, l2) in l0
template<typename Line, typename MulT = typename Line::value_type, MulT eps = std::is_same_v<typename Line::value_type, MulT> ? Line::eps_val : get_default_eps<MulT>()>
bool line_contain(const Line &l0, const Line &l1, const Line &l2, bool strict = true) {
    auto area_pair = [&](const Line &a, const Line &b) {
        return std::make_pair(cross(a[1] - a[0], b[0] - a[0]), cross(a[1] - a[0], b[1] - a[0]));
    };
    auto [a02X, a02Y] = area_pair(l0, l2);
    auto [a12X, a12Y] = area_pair(l1, l2);
    if (Geometry<MulT, eps>::cmp(a12X, a12Y) < 0) a12X *= -1, a12Y *= -1;
    return Geometry<MulT, eps>::cmp(MulT(a02Y) * MulT(a12X), MulT(a02X) * MulT(a12Y)) >= int(strict);
}

template<typename Line, typename MulT = typename Line::value_type, MulT eps = std::is_same_v<typename Line::value_type, MulT> ? Line::eps_val : get_default_eps<MulT>()>
std::vector<Line> half_plane_intersection(vector<Line> arr) {
    std::sort(ALL(arr), [&](const Line &a, const Line &b) -> int {
        if (!sameDirection(a, b))
            return polar(direction(a), direction(b));
        return side(a[0], a[1], b[1]) < 0;
    });
    std::deque<Line> dq(1, arr[0]);
    auto pop_back = [&](int t, const Line &p) {
        while (SZ(dq) >= t && !line_contain<Line, MulT, eps>(p, dq[SZ(dq) - 2], dq.back()))
            dq.pop_back();
    };
    auto pop_front = [&](int t, const Line &p) {
        while (SZ(dq) >= t && !line_contain<Line, MulT, eps>(p, dq[0], dq[1]))
            dq.pop_front();
    };
    for (auto p : arr)
        if (!sameDirection(dq.back(), p))
            pop_back(2, p), pop_front(2, p), dq.push_back(p);
    pop_back(3, dq[0]), pop_front(3, dq.back());
    return std::vector<Line>(dq.begin(), dq.end());
}
