#pragma once

#include "Polynomial/Polynomial.hpp"
#include "Numeric/Combination.hpp"

template <typename T>
std::vector<T> bell_number(int n) {
    Poly<T> f(n + 1);
    Combination<T> comb(n + 1);
    for (int i = 1; i <= n; ++i) f[i] = comb.ifac[i];
    auto res = f.Exp();
    for (int i = 0; i <= n; ++i) res[i] *= comb.fac[i];
    return std::vector<T>(res.begin(), res.end());
}
