#pragma once

#include "Polynomial/Polynomial.hpp"
#include "Numeric/Combination.hpp"

template <typename T>
std::vector<T> stirling_second_kind(int n) {
    Poly<T> f(n + 1), g(n + 1);
    Combination<T> comb(n + 1);
    for (int i = 0; i <= n; ++i) {
        f[i] = T(i).pow(n) * comb.ifac[i];
        g[i] = (i & 1) ? -comb.ifac[i] : comb.ifac[i];
    }
    return (f * g).isz(n + 1);
}
