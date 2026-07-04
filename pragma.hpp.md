---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/linear_algebra/matrix_product_mod_2.test.cpp
    title: test/1_library_checker/linear_algebra/matrix_product_mod_2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"pragma.hpp\"\n#ifdef __x86_64__\n    #pragma GCC optimize(\"\
    O3,unroll-loops\")\n    #pragma GCC target(\"avx2,bmi,bmi2,lzcnt,popcnt\")\n#endif\n"
  code: "#ifdef __x86_64__\n    #pragma GCC optimize(\"O3,unroll-loops\")\n    #pragma\
    \ GCC target(\"avx2,bmi,bmi2,lzcnt,popcnt\")\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: pragma.hpp
  requiredBy: []
  timestamp: '2026-07-04 18:47:24+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/linear_algebra/matrix_product_mod_2.test.cpp
documentation_of: pragma.hpp
layout: document
redirect_from:
- /library/pragma.hpp
- /library/pragma.hpp.html
title: pragma.hpp
---
