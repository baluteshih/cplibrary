---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: Numeric/Modint.hpp
    title: Numeric/Modint.hpp
  - icon: ':question:'
    path: Numeric/internal_math.hpp
    title: Numeric/internal_math.hpp
  _extendedRequiredBy:
  - icon: ':x:'
    path: Polynomial/Sqrt.hpp
    title: Polynomial/Sqrt.hpp
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/1_library_checker/number_theory/sqrt_mod.test.cpp
    title: test/1_library_checker/number_theory/sqrt_mod.test.cpp
  - icon: ':x:'
    path: test/1_library_checker/polynomial/sqrt_of_formal_power_series.test.cpp
    title: test/1_library_checker/polynomial/sqrt_of_formal_power_series.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Numeric/quadratic_residue.hpp\"\n\nint jacobi(int a, int\
    \ m) {\n    int s = 1;\n    for (; m > 1; ) {\n        a %= m;\n        if (a\
    \ == 0) return 0;\n        const int r = std::countr_zero(static_cast<unsigned\
    \ int>(a));\n        if ((r & 1) && ((m + 2) & 4)) s = -s;\n        a >>= r;\n\
    \        if (a & m & 2) s = -s;\n        std::swap(a, m);\n    }\n    return s;\n\
    }\n\n#line 2 \"Numeric/Modint.hpp\"\n\n// Reference: Atcoder Library https://github.com/atcoder/ac-library\n\
    #line 2 \"Numeric/internal_math.hpp\"\n// Reference: Atcoder Library https://github.com/atcoder/ac-library\n\
    \n#ifdef _MSC_VER\n#include <intrin.h>\n#endif\n\nnamespace internal {\nconstexpr\
    \ long long safe_mod(long long x, long long m) {\n    x %= m;\n    if (x < 0)\
    \ x += m;\n    return x;\n}\nconstexpr long long pow_mod_constexpr(long long x,\
    \ long long n, int m) {\n    if (m == 1) return 0;\n    unsigned int _m = (unsigned\
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
    }  // namespace internal\n#line 5 \"Numeric/Modint.hpp\"\n\ntemplate <int m, std::enable_if_t<(1\
    \ <= m)>* = nullptr>\nstruct static_modint : internal::static_modint_base {\n\
    \    using mint = static_modint;\n\n  public:\n    static constexpr int mod()\
    \ { return m; }\n    static mint raw(int v) {\n        mint x;\n        x._v =\
    \ v;\n        return x;\n    }\n\n    static_modint() : _v(0) {}\n    template\
    \ <class T, internal::is_signed_int_t<T>* = nullptr>\n    static_modint(T v) {\n\
    \        long long x = (long long)(v % (long long)(umod()));\n        if (x <\
    \ 0) x += umod();\n        _v = (unsigned int)(x);\n    }\n    template <class\
    \ T, internal::is_unsigned_int_t<T>* = nullptr>\n    static_modint(T v) {\n  \
    \      _v = (unsigned int)(v % umod());\n    }\n\n    unsigned int val() const\
    \ { return _v; }\n\n    mint& operator++() {\n        _v++;\n        if (_v ==\
    \ umod()) _v = 0;\n        return *this;\n    }\n    mint& operator--() {\n  \
    \      if (_v == 0) _v = umod();\n        _v--;\n        return *this;\n    }\n\
    \    mint operator++(int) {\n        mint result = *this;\n        ++*this;\n\
    \        return result;\n    }\n    mint operator--(int) {\n        mint result\
    \ = *this;\n        --*this;\n        return result;\n    }\n\n    mint& operator+=(const\
    \ mint& rhs) {\n        _v += rhs._v;\n        if (_v >= umod()) _v -= umod();\n\
    \        return *this;\n    }\n    mint& operator-=(const mint& rhs) {\n     \
    \   _v -= rhs._v;\n        if (_v >= umod()) _v += umod();\n        return *this;\n\
    \    }\n    mint& operator*=(const mint& rhs) {\n        unsigned long long z\
    \ = _v;\n        z *= rhs._v;\n        _v = (unsigned int)(z % umod());\n    \
    \    return *this;\n    }\n    mint& operator/=(const mint& rhs) { return *this\
    \ = *this * rhs.inv(); }\n\n    mint operator+() const { return *this; }\n   \
    \ mint operator-() const { return mint() - *this; }\n\n    mint pow(long long\
    \ n) const {\n        assert(0 <= n);\n        mint x = *this, r = 1;\n      \
    \  while (n) {\n            if (n & 1) r *= x;\n            x *= x;\n        \
    \    n >>= 1;\n        }\n        return r;\n    }\n    mint inv() const {\n \
    \       if (prime) {\n            assert(_v);\n            return pow(umod() -\
    \ 2);\n        } else {\n            auto eg = internal::inv_gcd(_v, m);\n   \
    \         assert(eg.first == 1);\n            return eg.second;\n        }\n \
    \   }\n\n    friend mint operator+(const mint& lhs, const mint& rhs) {\n     \
    \   return mint(lhs) += rhs;\n    }\n    friend mint operator-(const mint& lhs,\
    \ const mint& rhs) {\n        return mint(lhs) -= rhs;\n    }\n    friend mint\
    \ operator*(const mint& lhs, const mint& rhs) {\n        return mint(lhs) *= rhs;\n\
    \    }\n    friend mint operator/(const mint& lhs, const mint& rhs) {\n      \
    \  return mint(lhs) /= rhs;\n    }\n    friend bool operator==(const mint& lhs,\
    \ const mint& rhs) {\n        return lhs._v == rhs._v;\n    }\n    friend bool\
    \ operator!=(const mint& lhs, const mint& rhs) {\n        return lhs._v != rhs._v;\n\
    \    }\n    friend std::strong_ordering operator<=>(const mint& lhs, const mint&\
    \ rhs) {\n        return lhs._v <=> rhs._v;\n    }\n    friend ostream& operator<<(ostream&\
    \ os, const mint& v) {\n        os << v._v;\n        return os;\n    }\n    friend\
    \ istream& operator>>(istream& is, mint& v) {\n        long long x;\n        is\
    \ >> x;\n        x %= (long long)(umod());\n        if (x < 0) x += umod();\n\
    \        v._v = (unsigned int)(x);\n        return is;\n    }\n\n  private:\n\
    \    unsigned int _v;\n    static constexpr unsigned int umod() { return m; }\n\
    \    static constexpr bool prime = internal::is_prime<m>;\n};\n\nusing modint998244353\
    \ = static_modint<998244353>;\nusing modint1000000007 = static_modint<1000000007>;\n\
    #line 18 \"Numeric/quadratic_residue.hpp\"\n\ntemplate<class T>\nrequires std::derived_from<T,\
    \ internal::modint_base>\nT quadratic_residue(T a, bool &succ) {\n    succ = true;\n\
    \    if (T::mod() == 2) return a;\n    const int jc = jacobi(a.val(), T::mod());\n\
    \    if (jc == 0) return 0;\n    if (jc == -1) return succ = false, 0;\n    T\
    \ b, d;\n    std::mt19937 rng(880301);\n    for (; ; ) {\n        b = rng() %\
    \ T::mod();\n        d = b * b - a;\n        if (jacobi(d.val(), T::mod()) ==\
    \ -1) break;\n    }\n    T f0 = b, f1 = 1, g0 = 1, g1 = 0, tmp;\n    for (int\
    \ e = (1LL + T::mod()) >> 1; e; e >>= 1) {\n        if (e & 1) {\n           \
    \ tmp = g0 * f0 + d * g1 * f1;\n            g1 = g0 * f1 + g1 * f0;\n        \
    \    g0 = tmp;\n        }\n        tmp = f0 * f0 + d * f1 * f1;\n        f1 =\
    \ f0 * f1 * 2;\n        f0 = tmp;\n    }\n    return g0;\n}\n"
  code: "#pragma once\n\nint jacobi(int a, int m) {\n    int s = 1;\n    for (; m\
    \ > 1; ) {\n        a %= m;\n        if (a == 0) return 0;\n        const int\
    \ r = std::countr_zero(static_cast<unsigned int>(a));\n        if ((r & 1) &&\
    \ ((m + 2) & 4)) s = -s;\n        a >>= r;\n        if (a & m & 2) s = -s;\n \
    \       std::swap(a, m);\n    }\n    return s;\n}\n\n#include \"Numeric/Modint.hpp\"\
    \n\ntemplate<class T>\nrequires std::derived_from<T, internal::modint_base>\n\
    T quadratic_residue(T a, bool &succ) {\n    succ = true;\n    if (T::mod() ==\
    \ 2) return a;\n    const int jc = jacobi(a.val(), T::mod());\n    if (jc == 0)\
    \ return 0;\n    if (jc == -1) return succ = false, 0;\n    T b, d;\n    std::mt19937\
    \ rng(880301);\n    for (; ; ) {\n        b = rng() % T::mod();\n        d = b\
    \ * b - a;\n        if (jacobi(d.val(), T::mod()) == -1) break;\n    }\n    T\
    \ f0 = b, f1 = 1, g0 = 1, g1 = 0, tmp;\n    for (int e = (1LL + T::mod()) >> 1;\
    \ e; e >>= 1) {\n        if (e & 1) {\n            tmp = g0 * f0 + d * g1 * f1;\n\
    \            g1 = g0 * f1 + g1 * f0;\n            g0 = tmp;\n        }\n     \
    \   tmp = f0 * f0 + d * f1 * f1;\n        f1 = f0 * f1 * 2;\n        f0 = tmp;\n\
    \    }\n    return g0;\n}\n"
  dependsOn:
  - Numeric/Modint.hpp
  - Numeric/internal_math.hpp
  isVerificationFile: false
  path: Numeric/quadratic_residue.hpp
  requiredBy:
  - Polynomial/Sqrt.hpp
  timestamp: '2026-05-29 21:39:52+08:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/1_library_checker/polynomial/sqrt_of_formal_power_series.test.cpp
  - test/1_library_checker/number_theory/sqrt_mod.test.cpp
documentation_of: Numeric/quadratic_residue.hpp
layout: document
redirect_from:
- /library/Numeric/quadratic_residue.hpp
- /library/Numeric/quadratic_residue.hpp.html
title: Numeric/quadratic_residue.hpp
---
