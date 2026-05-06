---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: Misc/bigint.hpp
    title: Misc/bigint.hpp
  - icon: ':heavy_check_mark:'
    path: Polynomial/convolution_any_mod.hpp
    title: Polynomial/convolution_any_mod.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/biginteger/addition.test.cpp
    title: test/1_library_checker/biginteger/addition.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/biginteger/multiplication.test.cpp
    title: test/1_library_checker/biginteger/multiplication.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/convolution/convolution_mod_1000000007.test.cpp
    title: test/1_library_checker/convolution/convolution_mod_1000000007.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://maspypy.github.io/library/mod/crt3.hpp
  bundledCode: "#line 2 \"Numeric/crt.hpp\"\n\n// source: https://maspypy.github.io/library/mod/crt3.hpp\n\
    \nconstexpr unsigned int mod_pow_constexpr(unsigned long long a, unsigned long\
    \ long n, unsigned int mod) {\n    a %= mod;\n    unsigned long long res = 1;\n\
    \    for (int i = 0; i < 32; ++i) {\n        if (n & 1) res = res * a % mod;\n\
    \        a = a * a % mod, n /= 2;\n    }\n    return res;\n}\n\ntemplate <typename\
    \ T, unsigned int p0, unsigned int p1>\nT CRT2(unsigned long long a0, unsigned\
    \ long long a1) {\n    static_assert(p0 < p1);\n    static constexpr unsigned\
    \ long long x0_1 = mod_pow_constexpr(p0, p1 - 2, p1);\n    unsigned long long\
    \ c = (a1 - a0 + p1) * x0_1 % p1;\n    return a0 + c * p0;\n}\n\ntemplate <typename\
    \ T, unsigned int p0, unsigned int p1, unsigned int p2>\nT CRT3(unsigned long\
    \ long a0, unsigned long long a1, unsigned long long a2) {\n    static_assert(p0\
    \ < p1 && p1 < p2);\n    static constexpr unsigned long long x1 = mod_pow_constexpr(p0,\
    \ p1 - 2, p1);\n    static constexpr unsigned long long x2 = mod_pow_constexpr((unsigned\
    \ long long)(p0) * p1 % p2, p2 - 2, p2);\n    static constexpr unsigned long long\
    \ p01 = (unsigned long long)(p0) * p1;\n    unsigned long long c = (a1 - a0 +\
    \ p1) * x1 % p1;\n    unsigned long long ans_1 = a0 + c * p0;\n    c = (a2 - ans_1\
    \ % p2 + p2) * x2 % p2;\n    return T(ans_1) + T(c) * T(p01);\n}\n"
  code: "#pragma once\n\n// source: https://maspypy.github.io/library/mod/crt3.hpp\n\
    \nconstexpr unsigned int mod_pow_constexpr(unsigned long long a, unsigned long\
    \ long n, unsigned int mod) {\n    a %= mod;\n    unsigned long long res = 1;\n\
    \    for (int i = 0; i < 32; ++i) {\n        if (n & 1) res = res * a % mod;\n\
    \        a = a * a % mod, n /= 2;\n    }\n    return res;\n}\n\ntemplate <typename\
    \ T, unsigned int p0, unsigned int p1>\nT CRT2(unsigned long long a0, unsigned\
    \ long long a1) {\n    static_assert(p0 < p1);\n    static constexpr unsigned\
    \ long long x0_1 = mod_pow_constexpr(p0, p1 - 2, p1);\n    unsigned long long\
    \ c = (a1 - a0 + p1) * x0_1 % p1;\n    return a0 + c * p0;\n}\n\ntemplate <typename\
    \ T, unsigned int p0, unsigned int p1, unsigned int p2>\nT CRT3(unsigned long\
    \ long a0, unsigned long long a1, unsigned long long a2) {\n    static_assert(p0\
    \ < p1 && p1 < p2);\n    static constexpr unsigned long long x1 = mod_pow_constexpr(p0,\
    \ p1 - 2, p1);\n    static constexpr unsigned long long x2 = mod_pow_constexpr((unsigned\
    \ long long)(p0) * p1 % p2, p2 - 2, p2);\n    static constexpr unsigned long long\
    \ p01 = (unsigned long long)(p0) * p1;\n    unsigned long long c = (a1 - a0 +\
    \ p1) * x1 % p1;\n    unsigned long long ans_1 = a0 + c * p0;\n    c = (a2 - ans_1\
    \ % p2 + p2) * x2 % p2;\n    return T(ans_1) + T(c) * T(p01);\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: Numeric/crt.hpp
  requiredBy:
  - Polynomial/convolution_any_mod.hpp
  - Misc/bigint.hpp
  timestamp: '2026-02-27 19:30:58+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/convolution/convolution_mod_1000000007.test.cpp
  - test/1_library_checker/biginteger/multiplication.test.cpp
  - test/1_library_checker/biginteger/addition.test.cpp
documentation_of: Numeric/crt.hpp
layout: document
redirect_from:
- /library/Numeric/crt.hpp
- /library/Numeric/crt.hpp.html
title: Numeric/crt.hpp
---
