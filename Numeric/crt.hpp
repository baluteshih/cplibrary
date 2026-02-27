#pragma once

// source: https://maspypy.github.io/library/mod/crt3.hpp

constexpr unsigned int mod_pow_constexpr(unsigned long long a, unsigned long long n, unsigned int mod) {
    a %= mod;
    unsigned long long res = 1;
    for (int i = 0; i < 32; ++i) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod, n /= 2;
    }
    return res;
}

template <typename T, unsigned int p0, unsigned int p1>
T CRT2(unsigned long long a0, unsigned long long a1) {
    static_assert(p0 < p1);
    static constexpr unsigned long long x0_1 = mod_pow_constexpr(p0, p1 - 2, p1);
    unsigned long long c = (a1 - a0 + p1) * x0_1 % p1;
    return a0 + c * p0;
}

template <typename T, unsigned int p0, unsigned int p1, unsigned int p2>
T CRT3(unsigned long long a0, unsigned long long a1, unsigned long long a2) {
    static_assert(p0 < p1 && p1 < p2);
    static constexpr unsigned long long x1 = mod_pow_constexpr(p0, p1 - 2, p1);
    static constexpr unsigned long long x2 = mod_pow_constexpr((unsigned long long)(p0) * p1 % p2, p2 - 2, p2);
    static constexpr unsigned long long p01 = (unsigned long long)(p0) * p1;
    unsigned long long c = (a1 - a0 + p1) * x1 % p1;
    unsigned long long ans_1 = a0 + c * p0;
    c = (a2 - ans_1 % p2 + p2) * x2 % p2;
    return T(ans_1) + T(c) * T(p01);
}
