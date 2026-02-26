#pragma once

// source: https://maspypy.github.io/library/poly/convolution.hpp

#include "Numeric/Modint.hpp"
#include "Polynomial/NTT.hpp"
#include "Numeric/crt.hpp"

template <typename T>
requires std::derived_from<T, internal::modint_base>
vector<T> convolution_any_mod(vector<T> a, vector<T> b) {
    if (a.empty() || b.empty()) return vector<T>();
    int n = a.size(), m = b.size();
    static constexpr int p0 = 167772161;
    static constexpr int p1 = 469762049;
    static constexpr int p2 = 754974721;
    using mint0 = static_modint<p0>;
    using mint1 = static_modint<p1>;
    using mint2 = static_modint<p2>;
    vector<mint0> a0(n), b0(m);
    vector<mint1> a1(n), b1(m);
    vector<mint2> a2(n), b2(m);
    for (int i = 0; i < n; ++i)
        a0[i] = a[i].val(), a1[i] = a[i].val(), a2[i] = a[i].val();
    for (int i = 0; i < m; ++i)
        b0[i] = b[i].val(), b1[i] = b[i].val(), b2[i] = b[i].val();
    auto c0 = NTT<mint0>::convolution(a0, b0);
    auto c1 = NTT<mint1>::convolution(a1, b1);
    auto c2 = NTT<mint2>::convolution(a2, b2);
    vector<T> c(c0.size());
    for (int i = 0; i < n + m - 1; ++i)
        c[i] = CRT3<T, p0, p1, p2>(c0[i].val(), c1[i].val(), c2[i].val());
    return c;
}
