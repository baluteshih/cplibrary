#pragma once

#include "Numeric/Combination.hpp"
#include "Polynomial/Polynomial.hpp"

template <typename T>
std::vector<T> stirling_first_kind_row(int k, int n) {
    if (n < k) return {};
    Combination<T> comb(n + 1);
    auto inv = CombFunc::linear_inverse<T>(n + 1);
    Poly<T> res(n + 1);
    for (int i = 1; i <= n; ++i) res[i] = inv[i];
    res = res.Pow(k) * comb.ifac[k];
    for (int i = k; i <= n; ++i) {
        res[i] *= comb.fac[i];
        if ((i ^ k) & 1) res[i] *= T(-1);
    }
    return res;
}
