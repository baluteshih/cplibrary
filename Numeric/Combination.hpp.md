---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Numeric/internal_math.hpp
    title: Numeric/internal_math.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: Numbers/bell_number.hpp
    title: Numbers/bell_number.hpp
  - icon: ':heavy_check_mark:'
    path: Numbers/bernoulli_number.hpp
    title: Numbers/bernoulli_number.hpp
  - icon: ':heavy_check_mark:'
    path: Numbers/stirling_first_kind.hpp
    title: Numbers/stirling_first_kind.hpp
  - icon: ':heavy_check_mark:'
    path: Numbers/stirling_first_kind_row.hpp
    title: Numbers/stirling_first_kind_row.hpp
  - icon: ':heavy_check_mark:'
    path: Numbers/stirling_second_kind.hpp
    title: Numbers/stirling_second_kind.hpp
  - icon: ':heavy_check_mark:'
    path: Numbers/stirling_second_kind_row.hpp
    title: Numbers/stirling_second_kind_row.hpp
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
    path: test/1_library_checker/enumerative_combinatorics/stirling_number_of_the_first_kind.test.cpp
    title: test/1_library_checker/enumerative_combinatorics/stirling_number_of_the_first_kind.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/enumerative_combinatorics/stirling_number_of_the_first_kind_fixed_k.test.cpp
    title: test/1_library_checker/enumerative_combinatorics/stirling_number_of_the_first_kind_fixed_k.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/enumerative_combinatorics/stirling_number_of_the_second_kind.test.cpp
    title: test/1_library_checker/enumerative_combinatorics/stirling_number_of_the_second_kind.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/enumerative_combinatorics/stirling_number_of_the_second_kind_fixed_k.test.cpp
    title: test/1_library_checker/enumerative_combinatorics/stirling_number_of_the_second_kind_fixed_k.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/number_theory/bernoulli_number.test.cpp
    title: test/1_library_checker/number_theory/bernoulli_number.test.cpp
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
    \n// Reference: Atcoder Library https://github.com/atcoder/ac-library\n\n#ifdef\
    \ _MSC_VER\n#include <intrin.h>\n#endif\n\nnamespace internal {\nconstexpr long\
    \ long safe_mod(long long x, long long m) {\n    x %= m;\n    if (x < 0) x +=\
    \ m;\n    return x;\n}\nconstexpr long long pow_mod_constexpr(long long x, long\
    \ long n, int m) {\n    if (m == 1) return 0;\n    unsigned int _m = (unsigned\
    \ int)(m);\n    unsigned long long r = 1;\n    unsigned long long y = safe_mod(x,\
    \ m);\n    while (n) {\n        if (n & 1) r = (r * y) % _m;\n        y = (y *\
    \ y) % _m;\n        n >>= 1;\n    }\n    return r;\n}\nconstexpr bool is_prime_constexpr(int\
    \ n) {\n    if (n <= 1) return false;\n    if (n == 2 || n == 7 || n == 61) return\
    \ true;\n    if (n % 2 == 0) return false;\n    long long d = n - 1;\n    while\
    \ (d % 2 == 0) d /= 2;\n    constexpr long long bases[3] = {2, 7, 61};\n    for\
    \ (long long a : bases) {\n        long long t = d;\n        long long y = pow_mod_constexpr(a,\
    \ t, n);\n        while (t != n - 1 && y != 1 && y != n - 1)\n            y =\
    \ y * y % n, t <<= 1;\n        if (y != n - 1 && t % 2 == 0)\n            return\
    \ false;\n    }\n    return true;\n}\ntemplate <int n> constexpr bool is_prime\
    \ = is_prime_constexpr(n);\nconstexpr std::pair<long long, long long> inv_gcd(long\
    \ long a, long long b) {\n    a = safe_mod(a, b);\n    if (a == 0) return {b,\
    \ 0};\n    long long s = b, t = a, m0 = 0, m1 = 1;\n    while (t) {\n        long\
    \ long u = s / t;\n        s -= t * u, m0 -= m1 * u;\n        auto tmp = s;\n\
    \        s = t, t = tmp, tmp = m0, m0 = m1, m1 = tmp;\n    }\n    if (m0 < 0)\
    \ m0 += b / s;\n    return {s, m0};\n}\n}  // namespace internal\n\nnamespace\
    \ internal {\n#ifndef _MSC_VER\n    template <class T>\n        using is_signed_int128\
    \ =\n        typename std::conditional<std::is_same<T, __int128_t>::value ||\n\
    \        std::is_same<T, __int128>::value,\n        std::true_type,\n        std::false_type>::type;\n\
    \    template <class T>\n        using is_unsigned_int128 =\n        typename\
    \ std::conditional<std::is_same<T, __uint128_t>::value ||\n        std::is_same<T,\
    \ unsigned __int128>::value,\n        std::true_type,\n        std::false_type>::type;\n\
    \    template <class T>\n        using make_unsigned_int128 =\n        typename\
    \ std::conditional<std::is_same<T, __int128_t>::value,\n                 __uint128_t,\n\
    \                 unsigned __int128>;\n    template <class T>\n        using is_integral\
    \ = typename std::conditional<std::is_integral<T>::value ||\n        is_signed_int128<T>::value\
    \ ||\n        is_unsigned_int128<T>::value,\n        std::true_type,\n       \
    \ std::false_type>::type;\n    template <class T>\n        using is_signed_int\
    \ = typename std::conditional<(is_integral<T>::value &&\n                std::is_signed<T>::value)\
    \ ||\n        is_signed_int128<T>::value,\n        std::true_type,\n        std::false_type>::type;\n\
    \    template <class T>\n        using is_unsigned_int =\n        typename std::conditional<(is_integral<T>::value\
    \ &&\n                std::is_unsigned<T>::value) ||\n        is_unsigned_int128<T>::value,\n\
    \        std::true_type,\n        std::false_type>::type;\n    template <class\
    \ T>\n        using to_unsigned = typename std::conditional<\n        is_signed_int128<T>::value,\n\
    \        make_unsigned_int128<T>,\n        typename std::conditional<std::is_signed<T>::value,\n\
    \        std::make_unsigned<T>,\n        std::common_type<T>>::type>::type;\n\
    #else\n    template <class T> using is_integral = typename std::is_integral<T>;\n\
    \    template <class T>\n        using is_signed_int =\n        typename std::conditional<is_integral<T>::value\
    \ && std::is_signed<T>::value,\n                 std::true_type,\n           \
    \      std::false_type>::type;\n    template <class T>\n        using is_unsigned_int\
    \ =\n        typename std::conditional<is_integral<T>::value &&\n        std::is_unsigned<T>::value,\n\
    \        std::true_type,\n        std::false_type>::type;\n    template <class\
    \ T>\n        using to_unsigned = typename std::conditional<is_signed_int<T>::value,\n\
    \              std::make_unsigned<T>,\n              std::common_type<T>>::type;\n\
    #endif\n    template <class T> using is_signed_int_t = std::enable_if_t<is_signed_int<T>::value>;\n\
    \    template <class T> using is_unsigned_int_t = std::enable_if_t<is_unsigned_int<T>::value>;\n\
    \    template <class T> using to_unsigned_t = typename to_unsigned<T>::type;\n\
    \    struct modint_base {};\n    struct static_modint_base : modint_base {};\n\
    \    template <class T> using is_modint = std::is_base_of<modint_base, T>;\n \
    \   template <class T> using is_modint_t = std::enable_if_t<is_modint<T>::value>;\n\
    }  // namespace internal\n#line 4 \"Numeric/Combination.hpp\"\n\ntemplate<class\
    \ T>\nrequires std::derived_from<T, internal::modint_base>\nclass Combination\
    \ {\n    inline static int N = 1;\npublic:\n    inline static std::vector<T> fac\
    \ = {T(1)};\n    inline static std::vector<T> ifac = {T(1)};\n    Combination(int\
    \ n) { ensure_upper_bound(n); }\n    Combination(int n, T v) { \n        N = 1;\n\
    \        std::vector<T>(n, v.raw(1)).swap(fac);\n        std::vector<T>(n, v.raw(1)).swap(ifac);\n\
    \        ensure_upper_bound(n);\n    }\n    T C(int n, int m) {\n        if (n\
    \ < m || m < 0) return 0;\n        return fac[n] * ifac[m] * ifac[n - m];\n  \
    \  }\n    T invC(int n, int m) {\n        assert(n >= m && m >= 0);\n        return\
    \ ifac[n] * fac[m] * fac[n - m];\n    }\n    T P(int n, int m) {\n        if (n\
    \ < m) return 0;\n        return fac[n] * ifac[n - m];\n    }\n    T H(int n,\
    \ int m) {\n        return C(n + m - 1, m);\n    }\n    // a - b <= k and all\
    \ non-empty proper prefix have a - b < k\n    T extend_catalan(int a, int b, int\
    \ k) {\n        if (a - b == k) return C(a + b - 1, a - 1) - C(a + b - 1, b +\
    \ k);\n        return C(a + b, a) - C(a + b, b + k); \n    }\n    void ensure_upper_bound(int\
    \ n) {\n        if (N >= n) return;\n        fac.resize(n), ifac.resize(n);\n\
    \        for (int i = N; i < n; ++i)\n            fac[i] = fac[i - 1] * i;\n \
    \       ifac.back() = fac.back().inv();\n        for (int i = n - 2; i >= N; --i)\n\
    \            ifac[i] = ifac[i + 1] * (i + 1);\n        N = n;\n    }\n};\nnamespace\
    \ CombFunc {\ntemplate<class T>\nstd::vector<T> power(T base, int n) {\n    std::vector<T>\
    \ res(n + 1, 1);\n    for (int i = 1; i <= n; ++i)\n        res[i] = res[i - 1]\
    \ * base;\n    return res;\n}\ntemplate<class T>\nstd::vector<T> ipower(T base,\
    \ int n) {\n    return power(base.inv(), n);\n}\ntemplate<class T>\nstd::vector<T>\
    \ linear_inverse(int n) {\n    std::vector<T> res(n + 1, 1);\n    int MOD = T().mod();\n\
    \    for (int i = 2; i <= n; ++i) {\n        res[i] = res[MOD % i] * (MOD - MOD\
    \ / i); \n    }\n    return res;\n}\n}\n"
  code: "#pragma once\n\n#include \"Numeric/internal_math.hpp\"\n\ntemplate<class\
    \ T>\nrequires std::derived_from<T, internal::modint_base>\nclass Combination\
    \ {\n    inline static int N = 1;\npublic:\n    inline static std::vector<T> fac\
    \ = {T(1)};\n    inline static std::vector<T> ifac = {T(1)};\n    Combination(int\
    \ n) { ensure_upper_bound(n); }\n    Combination(int n, T v) { \n        N = 1;\n\
    \        std::vector<T>(n, v.raw(1)).swap(fac);\n        std::vector<T>(n, v.raw(1)).swap(ifac);\n\
    \        ensure_upper_bound(n);\n    }\n    T C(int n, int m) {\n        if (n\
    \ < m || m < 0) return 0;\n        return fac[n] * ifac[m] * ifac[n - m];\n  \
    \  }\n    T invC(int n, int m) {\n        assert(n >= m && m >= 0);\n        return\
    \ ifac[n] * fac[m] * fac[n - m];\n    }\n    T P(int n, int m) {\n        if (n\
    \ < m) return 0;\n        return fac[n] * ifac[n - m];\n    }\n    T H(int n,\
    \ int m) {\n        return C(n + m - 1, m);\n    }\n    // a - b <= k and all\
    \ non-empty proper prefix have a - b < k\n    T extend_catalan(int a, int b, int\
    \ k) {\n        if (a - b == k) return C(a + b - 1, a - 1) - C(a + b - 1, b +\
    \ k);\n        return C(a + b, a) - C(a + b, b + k); \n    }\n    void ensure_upper_bound(int\
    \ n) {\n        if (N >= n) return;\n        fac.resize(n), ifac.resize(n);\n\
    \        for (int i = N; i < n; ++i)\n            fac[i] = fac[i - 1] * i;\n \
    \       ifac.back() = fac.back().inv();\n        for (int i = n - 2; i >= N; --i)\n\
    \            ifac[i] = ifac[i + 1] * (i + 1);\n        N = n;\n    }\n};\nnamespace\
    \ CombFunc {\ntemplate<class T>\nstd::vector<T> power(T base, int n) {\n    std::vector<T>\
    \ res(n + 1, 1);\n    for (int i = 1; i <= n; ++i)\n        res[i] = res[i - 1]\
    \ * base;\n    return res;\n}\ntemplate<class T>\nstd::vector<T> ipower(T base,\
    \ int n) {\n    return power(base.inv(), n);\n}\ntemplate<class T>\nstd::vector<T>\
    \ linear_inverse(int n) {\n    std::vector<T> res(n + 1, 1);\n    int MOD = T().mod();\n\
    \    for (int i = 2; i <= n; ++i) {\n        res[i] = res[MOD % i] * (MOD - MOD\
    \ / i); \n    }\n    return res;\n}\n}\n"
  dependsOn:
  - Numeric/internal_math.hpp
  isVerificationFile: false
  path: Numeric/Combination.hpp
  requiredBy:
  - Numbers/bell_number.hpp
  - Numbers/stirling_second_kind_row.hpp
  - Numbers/stirling_second_kind.hpp
  - Numbers/stirling_first_kind.hpp
  - Numbers/stirling_first_kind_row.hpp
  - Numbers/bernoulli_number.hpp
  - Polynomial/lagrange_interpolate_iota.hpp
  - Polynomial/shift.hpp
  timestamp: '2026-06-29 01:18:59+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/enumerative_combinatorics/stirling_number_of_the_first_kind_fixed_k.test.cpp
  - test/1_library_checker/enumerative_combinatorics/bell_number.test.cpp
  - test/1_library_checker/enumerative_combinatorics/stirling_number_of_the_second_kind_fixed_k.test.cpp
  - test/1_library_checker/enumerative_combinatorics/stirling_number_of_the_first_kind.test.cpp
  - test/1_library_checker/enumerative_combinatorics/binomial_coefficient_prime_mod.test.cpp
  - test/1_library_checker/enumerative_combinatorics/stirling_number_of_the_second_kind.test.cpp
  - test/1_library_checker/number_theory/bernoulli_number.test.cpp
  - test/1_library_checker/polynomial/polynomial_taylor_shift.test.cpp
  - test/1_library_checker/polynomial/shift_of_sampling_points_of_polynomial.test.cpp
documentation_of: Numeric/Combination.hpp
layout: document
redirect_from:
- /library/Numeric/Combination.hpp
- /library/Numeric/Combination.hpp.html
title: Numeric/Combination.hpp
---
