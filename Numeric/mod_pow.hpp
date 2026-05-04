#pragma once

template<typename T>
T mod_pow(T a, long long n, T mod) {
    assert(n >= 0);
    if (mod == 1) return 0;
    a = ((a %= mod) < 0 ? a + mod : a);
    static auto mul = [&](T x, T y, T _mod) {
        if constexpr (sizeof(T) == 4) return (long long)x * y % _mod;
        else return (__int128)x * y % _mod;
    };
    T res = 1;
    for (; n; n >>= 1, a = mul(a, a, mod))
        if (n & 1)
            res = mul(res, a, mod);
    return res;
}
