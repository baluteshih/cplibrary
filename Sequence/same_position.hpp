#pragma once

#include "Algebra/IterableOf.hpp"

template<bool indexable_range = false, std::ranges::range C>
std::vector<int> previous_same_position(const C &arr) {
    std::conditional_t<indexable_range, std::vector<int>, std::map<std::ranges::range_value_t<C>, int>> prv;
    if constexpr (indexable_range) prv.resize(*std::ranges::max_element(arr) + 1);
    std::vector<int> res(arr.size());
    for (int i = 0; const auto &v : arr)
        res[i] = prv[v] - 1, prv[v] = ++i;
    return res;
}

template<bool indexable_range = false, std::ranges::range C>
std::vector<int> next_same_position(const C &arr) {
    std::vector<int> res = previous_same_position(arr | std::views::reverse);
    std::ranges::reverse(res);
    for (int &i : res) i = int(arr.size()) - i - 1;
    return res;
}
