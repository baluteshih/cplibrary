#pragma once

#include "Numeric/Modint.hpp"
#include "Polynomial/NTT.hpp"
#include "Numeric/crt.hpp"

template<int C, typename T>
std::vector<T> convolution(std::vector<T> a, std::vector<T> b) {
    static_assert(1 <= C && C <= 3, "NTT convolution must use 1, 2, or 3 primes.");
    if (a.empty() || b.empty()) return std::vector<T>();
    
    static constexpr int p0 = 167772161;
    static constexpr int p1 = 469762049;
    static constexpr int p2 = 754974721;

    auto do_ntt = [&](auto P_tag) {
        constexpr int P = decltype(P_tag)::value;
        using mint = static_modint<P>;
        std::vector<mint> a_mint(a.size()), b_mint(b.size());
        for (int i = 0; i < int(a.size()); ++i) a_mint[i] = a[i].val();
        for (int i = 0; i < int(b.size()); ++i) b_mint[i] = b[i].val();
        return NTT<mint>::convolution(a_mint, b_mint);
    };

    auto res = [&]() {
        if constexpr (C == 1)
            return std::make_tuple(do_ntt(std::integral_constant<int, p0>{}));
        else if constexpr (C == 2)
            return std::make_tuple(do_ntt(std::integral_constant<int, p0>{}),
                                   do_ntt(std::integral_constant<int, p1>{}));
        else
            return std::make_tuple(do_ntt(std::integral_constant<int, p0>{}),
                                   do_ntt(std::integral_constant<int, p1>{}),
                                   do_ntt(std::integral_constant<int, p2>{}));
    }();

    std::vector<T> c(std::get<0>(res).size());
    for (int i = 0; i < int(c.size()); ++i)
        if constexpr (C == 1)
            c[i] = T(std::get<0>(res)[i].val());
        else if constexpr (C == 2)
            c[i] = CRT2<T, p0, p1>(std::get<0>(res)[i].val(),
                                   std::get<1>(res)[i].val());
        else if constexpr (C == 3)
            c[i] = CRT3<T, p0, p1, p2>(std::get<0>(res)[i].val(),
                                       std::get<1>(res)[i].val(),
                                       std::get<2>(res)[i].val());
    return c;
}
