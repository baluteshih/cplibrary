#pragma once

#include "Algebra/IterableOf.hpp"

template<bool indexable_range = false, std::ranges::range C>
std::conditional_t<indexable_range, std::vector<std::vector<int>>, std::map<std::ranges::range_value_t<C>, std::vector<int>>> occur_position(const C &arr) {
    std::conditional_t<indexable_range, std::vector<std::vector<int>>, std::map<std::ranges::range_value_t<C>, std::vector<int>>> res;
    if constexpr (indexable_range) res.resize(*std::ranges::max_element(arr) + 1);
    for (int i = 0; const auto &v : arr)
        res[v].push_back(i++);
    return res;
}
