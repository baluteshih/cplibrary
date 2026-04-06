#pragma once

#include "Geometry/base.hpp"

template<typename T, T eps = get_default_eps<T>(), typename MulT = T>
std::pair<int, int> closest_pair(const std::vector<Pt<T, eps, MulT>> &dots) {
    int n = dots.size();
    assert(n >= 2);
    std::vector<int> idx(n);
    std::iota(idx.begin(), idx.end(), 0);
    std::ranges::sort(idx, [&](int a, int b) {
        return dots[a] < dots[b]; 
    });
    MulT min_d2 = std::numeric_limits<MulT>::max();
    std::pair<int, int> best = std::make_pair(-1, -1);
    auto sq = [](T x) { return MulT(x) * MulT(x); };
    auto update = [&](int i, int j) {
        MulT cur = dist2(dots[i], dots[j]);
        if (min_d2 > cur) {
            best = std::make_pair(i, j);
            min_d2 = cur;
        }
    };
    auto cmp_y = [&dots](int a, int b) {
        return dots[a].y < dots[b].y;  
    };
    std::multiset<int, decltype(cmp_y)> st(cmp_y);
    std::vector<typename std::multiset<int, decltype(cmp_y)>::iterator> its(n);
    for (int i = 0, lft = 0; i < n; ++i) {
        int u = idx[i];
        while (lft < i && sq(dots[u].x - dots[idx[lft]].x) >= min_d2)
            st.erase(its[lft++]);
        auto it = st.lower_bound(u);
        for (auto t = it; t != st.begin();) {
            if (sq(dots[u].y - dots[*(--t)].y) >= min_d2) break;
            update(*t, u);
        }
        for (auto t = it; t != st.end(); ++t) {
            if (sq(dots[u].y - dots[*t].y) >= min_d2) break;
            update(*t, u);
        }
        its[i] = st.insert(it, u);
    }
    return best;
}
