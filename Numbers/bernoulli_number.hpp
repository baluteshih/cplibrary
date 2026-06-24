#pragma once

#include "Polynomial/Polynomial.hpp"
#include "Numeric/Combination.hpp"

template <typename T>
std::vector<T> bernoulli_number(int n) {
    Poly<T> f(n + 1);
    Combination<T> comb(n + 2);
    for (int i = 0; i <= n; ++i) f[i] = comb.ifac[i + 1];
    auto res = f.Inv();
    for (int i = 0; i <= n; ++i) res[i] *= comb.fac[i];
    return std::vector<T>(res.begin(), res.end());
}
