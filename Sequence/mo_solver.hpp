#pragma once

#include "Algebra/NullFunc.hpp"

/*
intervals are [l, r)
query(idx): answer the idx-th query
add_left(l), remove_left(l)
add_right(r), remove_right(r): equal to add_left and remove_left if no specify
*/
template<typename F_query, typename F_add_left, typename F_remove_left, typename F_add_right = NullFunc, typename F_remove_right = NullFunc>
void mo_solver(const std::vector<std::pair<int, int>> &querys, F_query query, F_add_left add_left, F_remove_left remove_left, F_add_right add_right = NullFunc{}, F_remove_right remove_right = NullFunc{}) {
    constexpr bool useAddRight = !std::is_same_v<std::decay_t<decltype(add_right)>, NullFunc>;
    constexpr bool useRemoveRight = !std::is_same_v<std::decay_t<decltype(remove_right)>, NullFunc>;
    auto hilbert = [&](int n, int x, int y) {
        long long res = 0;
        for (int s = n / 2; s; s >>= 1) {
            int rx = (x & s) > 0;
            int ry = (y & s) > 0;
            res += s * 1ll * s * ((3 * rx) ^ ry);
            if (ry == 0) {
                if (rx == 1) x = s - 1 - x, y = s - 1 - y;
                std::swap(x, y);
            }
        }
        return res;
    }; // n = 2^k

    int n = 0;
    for (auto &[l, r] : querys) n = std::max(n, r);
    n = std::bit_ceil(static_cast<unsigned int>(n + 1));
    std::vector<long long> pos(querys.size());
    std::vector<int> idx(querys.size());
    for (int i = 0; auto &[l, r] : querys) pos[i++] = hilbert(n, l, r);
    std::iota(idx.begin(), idx.end(), 0);
    std::ranges::sort(idx, [&](int a, int b) { return pos[a] < pos[b]; });

    int cur_l = 0, cur_r = 0;
    for (int i : idx) {
        auto [l, r] = querys[i];
        while (cur_l > l) add_left(--cur_l);
        while (cur_r < r) 
            if constexpr (useAddRight) add_right(cur_r++);
            else add_left(cur_r++);
        while (cur_l < l) remove_left(cur_l++);
        while (cur_r > r)
            if constexpr (useRemoveRight) remove_right(--cur_r);
            else remove_left(--cur_r);
        query(i);
    }
}
