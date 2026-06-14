#pragma once

#include "Convolution/bitwise_transform.hpp"

template<typename T>
std::vector<T> and_convolution(std::vector<T> a, std::vector<T> b) {
    assert(a.size() == b.size());
    bitwise_transform::transform<bitwise_transform::superset, bitwise_transform::zeta>(a);  
    bitwise_transform::transform<bitwise_transform::superset, bitwise_transform::zeta>(b);
    int n = a.size();
    for (int i = 0; i < n; ++i) a[i] *= b[i];
    bitwise_transform::transform<bitwise_transform::superset, bitwise_transform::mobius>(a);
    return a;
}
