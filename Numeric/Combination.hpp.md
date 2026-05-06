---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: Numeric/internal_math.hpp
    title: Numeric/internal_math.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: Numbers/bell_number.hpp
    title: Numbers/bell_number.hpp
  - icon: ':heavy_check_mark:'
    path: Polynomial/lagrange_interpolate_iota.hpp
    title: Polynomial/lagrange_interpolate_iota.hpp
  - icon: ':heavy_check_mark:'
    path: Polynomial/shift.hpp
    title: Polynomial/shift.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/enumerative_combinatorics/bell_number.test.cpp
    title: test/1_library_checker/enumerative_combinatorics/bell_number.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/enumerative_combinatorics/binomial_coefficient_prime_mod.test.cpp
    title: test/1_library_checker/enumerative_combinatorics/binomial_coefficient_prime_mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/polynomial/polynomial_taylor_shift.test.cpp
    title: test/1_library_checker/polynomial/polynomial_taylor_shift.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/polynomial/shift_of_sampling_points_of_polynomial.test.cpp
    title: test/1_library_checker/polynomial/shift_of_sampling_points_of_polynomial.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Numeric/Combination.hpp\"\n\n#line 2 \"Numeric/internal_math.hpp\"\
    \n// Reference: Atcoder Library https://github.com/atcoder/ac-library\n\n#include\
    \ <utility>\n#include <cassert>\n#include <numeric>\n#include <type_traits>\n\n\
    #ifdef _MSC_VER\n#include <intrin.h>\n#endif\n\nnamespace internal {\n\n// @param\
    \ m `1 <= m`\n// @return x mod m\nconstexpr long long safe_mod(long long x, long\
    \ long m) {\n    x %= m;\n    if (x < 0) x += m;\n    return x;\n}\n\n// Fast\
    \ modular multiplication by barrett reduction\n// Reference: https://en.wikipedia.org/wiki/Barrett_reduction\n\
    // NOTE: reconsider after Ice Lake\nstruct barrett {\n    unsigned int _m;\n \
    \   unsigned long long im;\n    explicit barrett(unsigned int m) : _m(m), im((unsigned\
    \ long long)(-1) / m + 1) {}\n    unsigned int umod() const { return _m; }\n \
    \   unsigned int modulo(unsigned long long z) const {\n        if (_m == 1) return\
    \ 0;\n#ifdef _MSC_VER\n        unsigned long long x;\n        _umul128(z, im,\
    \ &x);\n#else\n        unsigned long long x = (unsigned long long)(((unsigned\
    \ __int128)(z)*im) >> 64);\n#endif\n        unsigned long long y = x * _m;\n \
    \       return (z - y + (z < y ? _m : 0));\n    }\n    unsigned int mul(unsigned\
    \ int a, unsigned int b) const {\n        return modulo((unsigned long long)a\
    \ * b);\n    }\n    unsigned long long floor(unsigned long long z) const {\n \
    \       if (_m == 1) return z;\n        unsigned long long x = (unsigned long\
    \ long)(((unsigned __int128)(z)*im) >> 64);\n        unsigned long long y = x\
    \ * _m;\n        return (z < y ? x - 1 : x);\n    }\n    std::pair<unsigned long\
    \ long, unsigned int> divmod(unsigned long long z) const {\n        if (_m ==\
    \ 1) return {z, 0};\n        unsigned long long x = (unsigned long long)(((unsigned\
    \ __int128)(z)*im) >> 64);\n        unsigned long long y = x * _m;\n        if\
    \ (z < y) return {x - 1, z - y + _m};\n        return {x, z - y};\n    }\n};\n\
    \n// @param n `0 <= n`\n// @param m `1 <= m`\n// @return `(x ** n) % m`\nconstexpr\
    \ long long pow_mod_constexpr(long long x, long long n, int m) {\n    if (m ==\
    \ 1) return 0;\n    unsigned int _m = (unsigned int)(m);\n    unsigned long long\
    \ r = 1;\n    unsigned long long y = safe_mod(x, m);\n    while (n) {\n      \
    \  if (n & 1) r = (r * y) % _m;\n        y = (y * y) % _m;\n        n >>= 1;\n\
    \    }\n    return r;\n}\n\n// Reference:\n// M. Forisek and J. Jancina,\n// Fast\
    \ Primality Testing for Integers That Fit into a Machine Word\n// @param n `0\
    \ <= n`\nconstexpr bool is_prime_constexpr(int n) {\n    if (n <= 1) return false;\n\
    \    if (n == 2 || n == 7 || n == 61) return true;\n    if (n % 2 == 0) return\
    \ false;\n    long long d = n - 1;\n    while (d % 2 == 0) d /= 2;\n    constexpr\
    \ long long bases[3] = {2, 7, 61};\n    for (long long a : bases) {\n        long\
    \ long t = d;\n        long long y = pow_mod_constexpr(a, t, n);\n        while\
    \ (t != n - 1 && y != 1 && y != n - 1) {\n            y = y * y % n;\n       \
    \     t <<= 1;\n        }\n        if (y != n - 1 && t % 2 == 0) {\n         \
    \   return false;\n        }\n    }\n    return true;\n}\ntemplate <int n> constexpr\
    \ bool is_prime = is_prime_constexpr(n);\n\n// @param b `1 <= b`\n// @return pair(g,\
    \ x) s.t. g = gcd(a, b), xa = g (mod b), 0 <= x < b/g\nconstexpr std::pair<long\
    \ long, long long> inv_gcd(long long a, long long b) {\n    a = safe_mod(a, b);\n\
    \    if (a == 0) return {b, 0};\n\n    // Contracts:\n    // [1] s - m0 * a =\
    \ 0 (mod b)\n    // [2] t - m1 * a = 0 (mod b)\n    // [3] s * |m1| + t * |m0|\
    \ <= b\n    long long s = b, t = a;\n    long long m0 = 0, m1 = 1;\n\n    while\
    \ (t) {\n        long long u = s / t;\n        s -= t * u;\n        m0 -= m1 *\
    \ u;  // |m1 * u| <= |m1| * s <= b\n\n        // [3]:\n        // (s - t * u)\
    \ * |m1| + t * |m0 - m1 * u|\n        // <= s * |m1| - t * u * |m1| + t * (|m0|\
    \ + |m1| * u)\n        // = s * |m1| + t * |m0| <= b\n\n        auto tmp = s;\n\
    \        s = t;\n        t = tmp;\n        tmp = m0;\n        m0 = m1;\n     \
    \   m1 = tmp;\n    }\n    // by [3]: |m0| <= b/g\n    // by g != b: |m0| < b/g\n\
    \    if (m0 < 0) m0 += b / s;\n    return {s, m0};\n}\n}  // namespace internal\n\
    \nnamespace internal {\n\n#ifndef _MSC_VER\n    template <class T>\n        using\
    \ is_signed_int128 =\n        typename std::conditional<std::is_same<T, __int128_t>::value\
    \ ||\n        std::is_same<T, __int128>::value,\n        std::true_type,\n   \
    \     std::false_type>::type;\n\n    template <class T>\n        using is_unsigned_int128\
    \ =\n        typename std::conditional<std::is_same<T, __uint128_t>::value ||\n\
    \        std::is_same<T, unsigned __int128>::value,\n        std::true_type,\n\
    \        std::false_type>::type;\n\n    template <class T>\n        using make_unsigned_int128\
    \ =\n        typename std::conditional<std::is_same<T, __int128_t>::value,\n \
    \                __uint128_t,\n                 unsigned __int128>;\n\n    template\
    \ <class T>\n        using is_integral = typename std::conditional<std::is_integral<T>::value\
    \ ||\n        is_signed_int128<T>::value ||\n        is_unsigned_int128<T>::value,\n\
    \        std::true_type,\n        std::false_type>::type;\n\n    template <class\
    \ T>\n        using is_signed_int = typename std::conditional<(is_integral<T>::value\
    \ &&\n                std::is_signed<T>::value) ||\n        is_signed_int128<T>::value,\n\
    \        std::true_type,\n        std::false_type>::type;\n\n    template <class\
    \ T>\n        using is_unsigned_int =\n        typename std::conditional<(is_integral<T>::value\
    \ &&\n                std::is_unsigned<T>::value) ||\n        is_unsigned_int128<T>::value,\n\
    \        std::true_type,\n        std::false_type>::type;\n\n    template <class\
    \ T>\n        using to_unsigned = typename std::conditional<\n        is_signed_int128<T>::value,\n\
    \        make_unsigned_int128<T>,\n        typename std::conditional<std::is_signed<T>::value,\n\
    \        std::make_unsigned<T>,\n        std::common_type<T>>::type>::type;\n\n\
    #else\n\n    template <class T> using is_integral = typename std::is_integral<T>;\n\
    \n    template <class T>\n        using is_signed_int =\n        typename std::conditional<is_integral<T>::value\
    \ && std::is_signed<T>::value,\n                 std::true_type,\n           \
    \      std::false_type>::type;\n\n    template <class T>\n        using is_unsigned_int\
    \ =\n        typename std::conditional<is_integral<T>::value &&\n        std::is_unsigned<T>::value,\n\
    \        std::true_type,\n        std::false_type>::type;\n\n    template <class\
    \ T>\n        using to_unsigned = typename std::conditional<is_signed_int<T>::value,\n\
    \              std::make_unsigned<T>,\n              std::common_type<T>>::type;\n\
    \n#endif\n\n    template <class T>\n        using is_signed_int_t = std::enable_if_t<is_signed_int<T>::value>;\n\
    \n    template <class T>\n        using is_unsigned_int_t = std::enable_if_t<is_unsigned_int<T>::value>;\n\
    \n    template <class T> using to_unsigned_t = typename to_unsigned<T>::type;\n\
    \n}  // namespace internal\n\n#line 229 \"Numeric/internal_math.hpp\"\n\n#ifdef\
    \ _MSC_VER\n#include <intrin.h>\n#endif\n\nnamespace internal {\n\n    struct\
    \ modint_base {};\n    struct static_modint_base : modint_base {};\n\n    template\
    \ <class T> using is_modint = std::is_base_of<modint_base, T>;\n    template <class\
    \ T> using is_modint_t = std::enable_if_t<is_modint<T>::value>;\n\n}  // namespace\
    \ internal\n#line 4 \"Numeric/Combination.hpp\"\n\ntemplate<class T>\nrequires\
    \ std::derived_from<T, internal::modint_base>\nclass Combination {\n    int N;\n\
    \    void init() {\n        for (int i = 1; i <= N; ++i)\n            fac[i] =\
    \ fac[i - 1] * i;\n        ifac.back() = fac.back().inv();\n        for (int i\
    \ = N - 1; i >= 0; --i)\n            ifac[i] = ifac[i + 1] * (i + 1);\n    }\n\
    public:\n    vector<T> fac, ifac;\n    Combination(int n): N(n), fac(N + 1, 1),\
    \ ifac(N + 1, 1) {\n        init();\n    }\n    Combination(int n, T base): N(n),\
    \ fac(N + 1, base.raw(1)), ifac(N + 1, base.raw(1)) {\n        init();\n    }\n\
    \    T C(int n, int m) {\n        if (n < m) return 0;\n        return fac[n]\
    \ * ifac[m] * ifac[n - m];\n    }\n    T P(int n, int m) {\n        if (n < m)\
    \ return 0;\n        return fac[n] * ifac[n - m];\n    }\n    T H(int n, int m)\
    \ {\n        return C(n + m - 1, m);\n    }\n};\nnamespace CombFunc {\ntemplate<class\
    \ T>\nvector<T> power(T base, int n) {\n    vector<T> res(n + 1, 1);\n    for\
    \ (int i = 1; i <= n; ++i)\n        res[i] = res[i - 1] * base;\n    return res;\n\
    }\ntemplate<class T>\nvector<T> ipower(T base, int n) {\n    return power(base.inv(),\
    \ n);\n}\ntemplate<class T>\nvector<T> linear_inverse(int n) {\n    vector<T>\
    \ res(n + 1, 1);\n    int MOD = T().mod();\n    for (int i = 2; i <= n; ++i) {\n\
    \        res[i] = res[MOD % i] * (MOD - MOD / i); \n    }\n    return res;\n}\n\
    }\n"
  code: "#pragma once\n\n#include \"Numeric/internal_math.hpp\"\n\ntemplate<class\
    \ T>\nrequires std::derived_from<T, internal::modint_base>\nclass Combination\
    \ {\n    int N;\n    void init() {\n        for (int i = 1; i <= N; ++i)\n   \
    \         fac[i] = fac[i - 1] * i;\n        ifac.back() = fac.back().inv();\n\
    \        for (int i = N - 1; i >= 0; --i)\n            ifac[i] = ifac[i + 1] *\
    \ (i + 1);\n    }\npublic:\n    vector<T> fac, ifac;\n    Combination(int n):\
    \ N(n), fac(N + 1, 1), ifac(N + 1, 1) {\n        init();\n    }\n    Combination(int\
    \ n, T base): N(n), fac(N + 1, base.raw(1)), ifac(N + 1, base.raw(1)) {\n    \
    \    init();\n    }\n    T C(int n, int m) {\n        if (n < m) return 0;\n \
    \       return fac[n] * ifac[m] * ifac[n - m];\n    }\n    T P(int n, int m) {\n\
    \        if (n < m) return 0;\n        return fac[n] * ifac[n - m];\n    }\n \
    \   T H(int n, int m) {\n        return C(n + m - 1, m);\n    }\n};\nnamespace\
    \ CombFunc {\ntemplate<class T>\nvector<T> power(T base, int n) {\n    vector<T>\
    \ res(n + 1, 1);\n    for (int i = 1; i <= n; ++i)\n        res[i] = res[i - 1]\
    \ * base;\n    return res;\n}\ntemplate<class T>\nvector<T> ipower(T base, int\
    \ n) {\n    return power(base.inv(), n);\n}\ntemplate<class T>\nvector<T> linear_inverse(int\
    \ n) {\n    vector<T> res(n + 1, 1);\n    int MOD = T().mod();\n    for (int i\
    \ = 2; i <= n; ++i) {\n        res[i] = res[MOD % i] * (MOD - MOD / i); \n   \
    \ }\n    return res;\n}\n}\n"
  dependsOn:
  - Numeric/internal_math.hpp
  isVerificationFile: false
  path: Numeric/Combination.hpp
  requiredBy:
  - Numbers/bell_number.hpp
  - Polynomial/lagrange_interpolate_iota.hpp
  - Polynomial/shift.hpp
  timestamp: '2026-05-04 10:37:09+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/polynomial/polynomial_taylor_shift.test.cpp
  - test/1_library_checker/polynomial/shift_of_sampling_points_of_polynomial.test.cpp
  - test/1_library_checker/enumerative_combinatorics/bell_number.test.cpp
  - test/1_library_checker/enumerative_combinatorics/binomial_coefficient_prime_mod.test.cpp
documentation_of: Numeric/Combination.hpp
layout: document
redirect_from:
- /library/Numeric/Combination.hpp
- /library/Numeric/Combination.hpp.html
title: Numeric/Combination.hpp
---
