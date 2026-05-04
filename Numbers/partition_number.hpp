#pragma once

#include "Polynomial/Polynomial.hpp"

template <typename T>
std::vector<T> partition_number(int n) {
    int m = std::sqrt(n) + 10;
    Poly<T> f(n + 1);
    for (int x = -m; x < m; ++x) {
        long long d = (long long)x * (3 * x - 1) / 2;
        if (d > n) continue;
        f[d] += (x % 2 == 0 ? 1 : -1);
    }
    auto res = f.Inv();
    return std::vector<T>(res.begin(), res.end());
}
