#pragma once

template<typename T>
bool _miller_rabin(T a, T n) {
    if ((a = a % n) == 0) return 1;
    if ((n & 1) ^ 1) return n == 2;
    static auto mul = [&](T x, T y, T mod) {
        if constexpr (sizeof(T) == 4) return (long long)x * y % mod;
        else return (__int128)x * y % mod;
    };
    T t = std::countr_zero(std::make_unsigned_t<T>(n - 1)), x = 1;
    T tmp = (n - 1) >> t;
    for (; tmp; tmp >>= 1, a = mul(a, a, n))
        if(tmp & 1) x = mul(x, a, n);
    if (x == 1 || x == n - 1) return 1;
    while (--t)
        if ((x = mul(x, x, n)) == n - 1) return 1;
    return 0;
}

template<typename T>
bool miller_rabin(T n) {
    if (n == 1) return false;
    static std::vector<T> _base[4] = {{2, 7, 61}, {2, 13, 23, 1662803}, {2, 3, 5, 7, 11, 13}, {2, 325, 9375, 28178, 450775, 9780504, 1795265022}};
    std::vector<T> base =
        (n < 4759123141ll) ? _base[0] :
        (n < 1122004669633ll) ? _base[1] :
        (n < 3474749660383ll) ? _base[2] : _base[3];
    for (T b : base)
        if (!_miller_rabin(b, n))
            return false;
    return true;
}
