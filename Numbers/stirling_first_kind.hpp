#pragma once

#include "Polynomial/Polynomial.hpp"
#include "Polynomial/shift.hpp"

template <typename T>
std::vector<T> stirling_first_kind(int n) {
    if (n <= 0) return {T(1)};
    int lg = std::bit_width(static_cast<unsigned int>(n));
    Poly<T> f({0, 1});
    for (int i = lg - 2; i >= 0; --i) {
        int _n = n >> i;
        f *= Poly<T>(f).shift(T(_n >> 1));
        if (_n & 1) f = (f << 1) + (f * T(_n - 1)).isz(f.size() + 1);
    }
    for (int i = (n & 1) ^ 1; i <= n; i += 2) f[i] *= T(-1);
    return f;
}
