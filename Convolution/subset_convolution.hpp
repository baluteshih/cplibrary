#pragma once

#include "Convolution/bitwise_transform.hpp"

template<typename T>
std::vector<T> subset_convolution(std::vector<T> a, std::vector<T> b) {
    assert(a.size() == b.size());
    auto ra = bitwise_transform::ranked_zeta(a);
    auto rb = a == b ? ra : bitwise_transform::ranked_zeta(b);
    int n = a.size(), lg = std::__lg(n);
    std::vector<std::vector<T>> store(lg + 1, std::vector<T>(n));
    for (int i = 0; i <= lg; ++i)
        for (int j = 0; j <= i; ++j)
            for (int x = 0; x < n; ++x)
                store[i][x] += ra[j][x] * rb[i - j][x]; 
    return bitwise_transform::ranked_mobius(store);
}
