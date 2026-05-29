#pragma once
// Reference: Atcoder Library https://github.com/atcoder/ac-library

#ifdef _MSC_VER
#include <intrin.h>
#endif

namespace internal {
constexpr long long safe_mod(long long x, long long m) {
    x %= m;
    if (x < 0) x += m;
    return x;
}
constexpr long long pow_mod_constexpr(long long x, long long n, int m) {
    if (m == 1) return 0;
    unsigned int _m = (unsigned int)(m);
    unsigned long long r = 1;
    unsigned long long y = safe_mod(x, m);
    while (n) {
        if (n & 1) r = (r * y) % _m;
        y = (y * y) % _m;
        n >>= 1;
    }
    return r;
}
constexpr bool is_prime_constexpr(int n) {
    if (n <= 1) return false;
    if (n == 2 || n == 7 || n == 61) return true;
    if (n % 2 == 0) return false;
    long long d = n - 1;
    while (d % 2 == 0) d /= 2;
    constexpr long long bases[3] = {2, 7, 61};
    for (long long a : bases) {
        long long t = d;
        long long y = pow_mod_constexpr(a, t, n);
        while (t != n - 1 && y != 1 && y != n - 1)
            y = y * y % n, t <<= 1;
        if (y != n - 1 && t % 2 == 0)
            return false;
    }
    return true;
}
template <int n> constexpr bool is_prime = is_prime_constexpr(n);
constexpr std::pair<long long, long long> inv_gcd(long long a, long long b) {
    a = safe_mod(a, b);
    if (a == 0) return {b, 0};
    long long s = b, t = a, m0 = 0, m1 = 1;
    while (t) {
        long long u = s / t;
        s -= t * u, m0 -= m1 * u;
        auto tmp = s;
        s = t, t = tmp, tmp = m0, m0 = m1, m1 = tmp;
    }
    if (m0 < 0) m0 += b / s;
    return {s, m0};
}
}  // namespace internal

namespace internal {
#ifndef _MSC_VER
    template <class T>
        using is_signed_int128 =
        typename std::conditional<std::is_same<T, __int128_t>::value ||
        std::is_same<T, __int128>::value,
        std::true_type,
        std::false_type>::type;
    template <class T>
        using is_unsigned_int128 =
        typename std::conditional<std::is_same<T, __uint128_t>::value ||
        std::is_same<T, unsigned __int128>::value,
        std::true_type,
        std::false_type>::type;
    template <class T>
        using make_unsigned_int128 =
        typename std::conditional<std::is_same<T, __int128_t>::value,
                 __uint128_t,
                 unsigned __int128>;
    template <class T>
        using is_integral = typename std::conditional<std::is_integral<T>::value ||
        is_signed_int128<T>::value ||
        is_unsigned_int128<T>::value,
        std::true_type,
        std::false_type>::type;
    template <class T>
        using is_signed_int = typename std::conditional<(is_integral<T>::value &&
                std::is_signed<T>::value) ||
        is_signed_int128<T>::value,
        std::true_type,
        std::false_type>::type;
    template <class T>
        using is_unsigned_int =
        typename std::conditional<(is_integral<T>::value &&
                std::is_unsigned<T>::value) ||
        is_unsigned_int128<T>::value,
        std::true_type,
        std::false_type>::type;
    template <class T>
        using to_unsigned = typename std::conditional<
        is_signed_int128<T>::value,
        make_unsigned_int128<T>,
        typename std::conditional<std::is_signed<T>::value,
        std::make_unsigned<T>,
        std::common_type<T>>::type>::type;
#else
    template <class T> using is_integral = typename std::is_integral<T>;
    template <class T>
        using is_signed_int =
        typename std::conditional<is_integral<T>::value && std::is_signed<T>::value,
                 std::true_type,
                 std::false_type>::type;
    template <class T>
        using is_unsigned_int =
        typename std::conditional<is_integral<T>::value &&
        std::is_unsigned<T>::value,
        std::true_type,
        std::false_type>::type;
    template <class T>
        using to_unsigned = typename std::conditional<is_signed_int<T>::value,
              std::make_unsigned<T>,
              std::common_type<T>>::type;
#endif
    template <class T> using is_signed_int_t = std::enable_if_t<is_signed_int<T>::value>;
    template <class T> using is_unsigned_int_t = std::enable_if_t<is_unsigned_int<T>::value>;
    template <class T> using to_unsigned_t = typename to_unsigned<T>::type;
    struct modint_base {};
    struct static_modint_base : modint_base {};
    template <class T> using is_modint = std::is_base_of<modint_base, T>;
    template <class T> using is_modint_t = std::enable_if_t<is_modint<T>::value>;
}  // namespace internal
