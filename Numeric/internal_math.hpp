#pragma once
// Reference: Atcoder Library https://github.com/atcoder/ac-library

#include <utility>
#include <cassert>
#include <numeric>
#include <type_traits>

#ifdef _MSC_VER
#include <intrin.h>
#endif

namespace internal {

// @param m `1 <= m`
// @return x mod m
constexpr long long safe_mod(long long x, long long m) {
    x %= m;
    if (x < 0) x += m;
    return x;
}

// Fast modular multiplication by barrett reduction
// Reference: https://en.wikipedia.org/wiki/Barrett_reduction
// NOTE: reconsider after Ice Lake
struct barrett {
    unsigned int _m;
    unsigned long long im;
    explicit barrett(unsigned int m) : _m(m), im((unsigned long long)(-1) / m + 1) {}
    unsigned int umod() const { return _m; }
    unsigned int modulo(unsigned long long z) const {
        if (_m == 1) return 0;
#ifdef _MSC_VER
        unsigned long long x;
        _umul128(z, im, &x);
#else
        unsigned long long x = (unsigned long long)(((unsigned __int128)(z)*im) >> 64);
#endif
        unsigned long long y = x * _m;
        return (z - y + (z < y ? _m : 0));
    }
    unsigned int mul(unsigned int a, unsigned int b) const {
        return modulo((unsigned long long)a * b);
    }
    unsigned long long floor(unsigned long long z) const {
        if (_m == 1) return z;
        unsigned long long x = (unsigned long long)(((unsigned __int128)(z)*im) >> 64);
        unsigned long long y = x * _m;
        return (z < y ? x - 1 : x);
    }
    std::pair<unsigned long long, unsigned int> divmod(unsigned long long z) const {
        if (_m == 1) return {z, 0};
        unsigned long long x = (unsigned long long)(((unsigned __int128)(z)*im) >> 64);
        unsigned long long y = x * _m;
        if (z < y) return {x - 1, z - y + _m};
        return {x, z - y};
    }
};

// @param n `0 <= n`
// @param m `1 <= m`
// @return `(x ** n) % m`
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

// Reference:
// M. Forisek and J. Jancina,
// Fast Primality Testing for Integers That Fit into a Machine Word
// @param n `0 <= n`
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
        while (t != n - 1 && y != 1 && y != n - 1) {
            y = y * y % n;
            t <<= 1;
        }
        if (y != n - 1 && t % 2 == 0) {
            return false;
        }
    }
    return true;
}
template <int n> constexpr bool is_prime = is_prime_constexpr(n);

// @param b `1 <= b`
// @return pair(g, x) s.t. g = gcd(a, b), xa = g (mod b), 0 <= x < b/g
constexpr std::pair<long long, long long> inv_gcd(long long a, long long b) {
    a = safe_mod(a, b);
    if (a == 0) return {b, 0};

    // Contracts:
    // [1] s - m0 * a = 0 (mod b)
    // [2] t - m1 * a = 0 (mod b)
    // [3] s * |m1| + t * |m0| <= b
    long long s = b, t = a;
    long long m0 = 0, m1 = 1;

    while (t) {
        long long u = s / t;
        s -= t * u;
        m0 -= m1 * u;  // |m1 * u| <= |m1| * s <= b

        // [3]:
        // (s - t * u) * |m1| + t * |m0 - m1 * u|
        // <= s * |m1| - t * u * |m1| + t * (|m0| + |m1| * u)
        // = s * |m1| + t * |m0| <= b

        auto tmp = s;
        s = t;
        t = tmp;
        tmp = m0;
        m0 = m1;
        m1 = tmp;
    }
    // by [3]: |m0| <= b/g
    // by g != b: |m0| < b/g
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

    template <class T>
        using is_signed_int_t = std::enable_if_t<is_signed_int<T>::value>;

    template <class T>
        using is_unsigned_int_t = std::enable_if_t<is_unsigned_int<T>::value>;

    template <class T> using to_unsigned_t = typename to_unsigned<T>::type;

}  // namespace internal

#include <cassert>
#include <numeric>
#include <type_traits>

#ifdef _MSC_VER
#include <intrin.h>
#endif

namespace internal {

    struct modint_base {};
    struct static_modint_base : modint_base {};

    template <class T> using is_modint = std::is_base_of<modint_base, T>;
    template <class T> using is_modint_t = std::enable_if_t<is_modint<T>::value>;

}  // namespace internal
