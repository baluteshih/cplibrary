#pragma once

#include "Polynomial/Polynomial.hpp"
#include "Numeric/Combination.hpp"

// given f(0),...,f(n-1), return f(c + i) for all 0 <= i < m, 5e5/408ms
// source: https://maspypy.github.io/library/poly/lagrange_interpolate_iota.hpp
template<class T>
std::vector<T> lagrange_interpolate_iota(const std::vector<T> &f, T c, int m) {
    const int k = f.size();
    Poly<T> a(f);
    Combination<T> comb(k);
    for (int i = 0; i < k; ++i) {
        a[i] *= comb.ifac[i] * comb.ifac[k - i - 1];
        if ((k - i - 1) & 1) a[i] = -a[i];
    }
    Poly<T> b(k + m - 1);
    for (int i = 0; i < k + m - 1; ++i) {
        T v = c + T(i - k + 1);
        if (v == 0) b[i] = 0;
        else b[i] = 1 / v;
    }
    a = a * b;
    std::vector<T> res(m);
    int L = 0, R = 0;
    int zero = 0;
    std::deque<T> prod;
    T prod_v = 1;
    auto push = [&](T x) {
        prod.push_back(x);
        if (x == 0) ++zero;
        else prod_v *= x;
    };
    auto pop = [&]() {
        if (prod[0] == 0) --zero;
        else prod_v /= prod[0];
        prod.pop_front();
    };
    for (int i = 0; i < m; ++i) {
        while (L < i) pop(), ++L;
        while (R - L < k) push(c + T((R++) - k + 1));
        if (zero)
            res[i] = f[(c + i).val()];
        else
            res[i] = a[i + k - 1] * prod_v;
    }
    return res;
}
