#pragma once

#include "Convolution/bitwise_transform.hpp"
#include "Numeric/internal_math.hpp"

template<typename T>
std::vector<T> xor_convolution(std::vector<T> a, std::vector<T> b) {
    assert(a.size() == b.size());
    if (a == b) 
        bitwise_transform::transform<bitwise_transform::popcount>(a), b = a;
    else {
        bitwise_transform::transform<bitwise_transform::popcount>(a);
        bitwise_transform::transform<bitwise_transform::popcount>(b);
    }
    int n = a.size();
    for (int i = 0; i < n; ++i) a[i] *= b[i];
    bitwise_transform::transform<bitwise_transform::popcount>(a);
    if constexpr (std::derived_from<T, internal::modint_base>) {
        T inv = T(n).inv();
        for (int i = 0; i < n; ++i) a[i] *= inv;
    }
    else {
        for (int i = 0; i < n; ++i) a[i] /= n;
    }
    return a;
}
