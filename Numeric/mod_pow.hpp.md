---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: Numeric/Binomial.hpp
    title: Numeric/Binomial.hpp
  - icon: ':heavy_check_mark:'
    path: Numeric/primitive_root.hpp
    title: Numeric/primitive_root.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/enumerative_combinatorics/binomial_coefficient.test.cpp
    title: test/1_library_checker/enumerative_combinatorics/binomial_coefficient.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/number_theory/primitive_root.test.cpp
    title: test/1_library_checker/number_theory/primitive_root.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Numeric/mod_pow.hpp\"\n\ntemplate<typename T>\nT mod_pow(T\
    \ a, long long n, T mod) {\n    assert(n >= 0);\n    if (mod == 1) return 0;\n\
    \    a = ((a %= mod) < 0 ? a + mod : a);\n    static auto mul = [&](T x, T y,\
    \ T _mod) {\n        if constexpr (sizeof(T) == 4) return (long long)x * y % _mod;\n\
    \        else return (__int128)x * y % _mod;\n    };\n    T res = 1;\n    for\
    \ (; n; n >>= 1, a = mul(a, a, mod))\n        if (n & 1)\n            res = mul(res,\
    \ a, mod);\n    return res;\n}\n"
  code: "#pragma once\n\ntemplate<typename T>\nT mod_pow(T a, long long n, T mod)\
    \ {\n    assert(n >= 0);\n    if (mod == 1) return 0;\n    a = ((a %= mod) < 0\
    \ ? a + mod : a);\n    static auto mul = [&](T x, T y, T _mod) {\n        if constexpr\
    \ (sizeof(T) == 4) return (long long)x * y % _mod;\n        else return (__int128)x\
    \ * y % _mod;\n    };\n    T res = 1;\n    for (; n; n >>= 1, a = mul(a, a, mod))\n\
    \        if (n & 1)\n            res = mul(res, a, mod);\n    return res;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: Numeric/mod_pow.hpp
  requiredBy:
  - Numeric/primitive_root.hpp
  - Numeric/Binomial.hpp
  timestamp: '2026-05-04 10:37:09+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/number_theory/primitive_root.test.cpp
  - test/1_library_checker/enumerative_combinatorics/binomial_coefficient.test.cpp
documentation_of: Numeric/mod_pow.hpp
layout: document
redirect_from:
- /library/Numeric/mod_pow.hpp
- /library/Numeric/mod_pow.hpp.html
title: Numeric/mod_pow.hpp
---
