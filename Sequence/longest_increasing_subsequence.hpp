#pragma once

#include "DataStructure/Discretization.hpp"
#include "DataStructure/BIT.hpp"
#include "Algebra/Monoid/max_v.hpp"

template<bool strict = true, typename T = int>
std::vector<int> longest_increasing_subsequence(const std::vector<T> &arr) {
    Discretization<T> val(arr.begin(), arr.end());
    val.build();
    BIT<max_v<std::pair<int, int>>> bit(val.size());
    std::vector<int> dp(arr.size()), tr(arr.size());
    for (int i = 0; i < int(arr.size()); ++i) {
        int cur = val.idx(arr[i]);
        auto [v, idx] = bit.prefix(cur - strict).val;
        if (v <= 0) dp[i] = 1, tr[i] = -1;
        else dp[i] = v + 1, tr[i] = idx;
        bit.modify(cur, std::make_pair(dp[i], i));
    }
    std::vector<int> res;
    for (int mx = std::ranges::max_element(dp) - dp.begin(); mx != -1; mx = tr[mx])
        res.push_back(mx);
    std::ranges::reverse(res);
    return res;
}
