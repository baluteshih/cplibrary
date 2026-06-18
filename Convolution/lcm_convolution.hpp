#pragma once

#include "Numeric/factor_transform.hpp"

template<typename T>
std::vector<T> lcm_convolution(std::vector<T> a, std::vector<T> b) {
    assert(a.size() == b.size());
    if (a == b)
        factor_transform::transform<factor_transform::divisor, factor_transform::zeta>(a), b = a; 
    else {
        factor_transform::transform<factor_transform::divisor, factor_transform::zeta>(a);  
        factor_transform::transform<factor_transform::divisor, factor_transform::zeta>(b);
    }
    int n = a.size();
    for (int i = 0; i < n; ++i) a[i] *= b[i];
    factor_transform::transform<factor_transform::divisor, factor_transform::mobius>(a);
    return a;
}
