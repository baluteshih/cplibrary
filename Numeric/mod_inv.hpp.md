---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: Numeric/Binomial.hpp
    title: Numeric/Binomial.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/enumerative_combinatorics/binomial_coefficient.test.cpp
    title: test/1_library_checker/enumerative_combinatorics/binomial_coefficient.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Numeric/mod_inv.hpp\"\n\ntemplate<typename T>\nT mod_inv(T\
    \ val, T mod) {\n    if (mod == 0) return 0;\n    mod = std::abs(mod);\n    val\
    \ %= mod;\n    if (val < 0) val += mod;\n    T a = val, b = mod, u = 1, v = 0,\
    \ t;\n    while (b > 0) {\n        t = a / b;\n        swap(a -= t * b, b), swap(u\
    \ -= t * v, v);\n    }\n    if (u < 0) u += mod;\n    return u;\n}\n"
  code: "#pragma once\n\ntemplate<typename T>\nT mod_inv(T val, T mod) {\n    if (mod\
    \ == 0) return 0;\n    mod = std::abs(mod);\n    val %= mod;\n    if (val < 0)\
    \ val += mod;\n    T a = val, b = mod, u = 1, v = 0, t;\n    while (b > 0) {\n\
    \        t = a / b;\n        swap(a -= t * b, b), swap(u -= t * v, v);\n    }\n\
    \    if (u < 0) u += mod;\n    return u;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: Numeric/mod_inv.hpp
  requiredBy:
  - Numeric/Binomial.hpp
  timestamp: '2026-05-04 10:37:09+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/enumerative_combinatorics/binomial_coefficient.test.cpp
documentation_of: Numeric/mod_inv.hpp
layout: document
redirect_from:
- /library/Numeric/mod_inv.hpp
- /library/Numeric/mod_inv.hpp.html
title: Numeric/mod_inv.hpp
---
