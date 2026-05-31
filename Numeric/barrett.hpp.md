---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: Numeric/Binomial.hpp
    title: Numeric/Binomial.hpp
  - icon: ':heavy_check_mark:'
    path: Numeric/DynamicModint.hpp
    title: Numeric/DynamicModint.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/enumerative_combinatorics/binomial_coefficient.test.cpp
    title: test/1_library_checker/enumerative_combinatorics/binomial_coefficient.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/enumerative_combinatorics/binomial_coefficient_prime_mod.test.cpp
    title: test/1_library_checker/enumerative_combinatorics/binomial_coefficient_prime_mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/linear_algebra/matrix_det_arbitrary_mod.test.cpp
    title: test/1_library_checker/linear_algebra/matrix_det_arbitrary_mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/number_theory/sqrt_mod.test.cpp
    title: test/1_library_checker/number_theory/sqrt_mod.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://github.com/atcoder/ac-library
  bundledCode: "#line 2 \"Numeric/barrett.hpp\"\n// Reference: Atcoder Library https://github.com/atcoder/ac-library\n\
    \n#ifdef _MSC_VER\n#include <intrin.h>\n#endif\n\nstruct barrett {\n    unsigned\
    \ int _m;\n    unsigned long long im;\n    explicit barrett(unsigned int m) :\
    \ _m(m), im((unsigned long long)(-1) / m + 1) {}\n    unsigned int umod() const\
    \ { return _m; }\n    unsigned int modulo(unsigned long long z) const {\n    \
    \    if (_m == 1) return 0;\n#ifdef _MSC_VER\n        unsigned long long x;\n\
    \        _umul128(z, im, &x);\n#else\n        unsigned long long x = (unsigned\
    \ long long)(((unsigned __int128)(z)*im) >> 64);\n#endif\n        unsigned long\
    \ long y = x * _m;\n        return (z - y + (z < y ? _m : 0));\n    }\n    unsigned\
    \ int mul(unsigned int a, unsigned int b) const {\n        return modulo((unsigned\
    \ long long)a * b);\n    }\n    unsigned long long floor(unsigned long long z)\
    \ const {\n        if (_m == 1) return z;\n        unsigned long long x = (unsigned\
    \ long long)(((unsigned __int128)(z)*im) >> 64);\n        unsigned long long y\
    \ = x * _m;\n        return (z < y ? x - 1 : x);\n    }\n    std::pair<unsigned\
    \ long long, unsigned int> divmod(unsigned long long z) const {\n        if (_m\
    \ == 1) return {z, 0};\n        unsigned long long x = (unsigned long long)(((unsigned\
    \ __int128)(z)*im) >> 64);\n        unsigned long long y = x * _m;\n        if\
    \ (z < y) return {x - 1, z - y + _m};\n        return {x, z - y};\n    }\n};\n"
  code: "#pragma once\n// Reference: Atcoder Library https://github.com/atcoder/ac-library\n\
    \n#ifdef _MSC_VER\n#include <intrin.h>\n#endif\n\nstruct barrett {\n    unsigned\
    \ int _m;\n    unsigned long long im;\n    explicit barrett(unsigned int m) :\
    \ _m(m), im((unsigned long long)(-1) / m + 1) {}\n    unsigned int umod() const\
    \ { return _m; }\n    unsigned int modulo(unsigned long long z) const {\n    \
    \    if (_m == 1) return 0;\n#ifdef _MSC_VER\n        unsigned long long x;\n\
    \        _umul128(z, im, &x);\n#else\n        unsigned long long x = (unsigned\
    \ long long)(((unsigned __int128)(z)*im) >> 64);\n#endif\n        unsigned long\
    \ long y = x * _m;\n        return (z - y + (z < y ? _m : 0));\n    }\n    unsigned\
    \ int mul(unsigned int a, unsigned int b) const {\n        return modulo((unsigned\
    \ long long)a * b);\n    }\n    unsigned long long floor(unsigned long long z)\
    \ const {\n        if (_m == 1) return z;\n        unsigned long long x = (unsigned\
    \ long long)(((unsigned __int128)(z)*im) >> 64);\n        unsigned long long y\
    \ = x * _m;\n        return (z < y ? x - 1 : x);\n    }\n    std::pair<unsigned\
    \ long long, unsigned int> divmod(unsigned long long z) const {\n        if (_m\
    \ == 1) return {z, 0};\n        unsigned long long x = (unsigned long long)(((unsigned\
    \ __int128)(z)*im) >> 64);\n        unsigned long long y = x * _m;\n        if\
    \ (z < y) return {x - 1, z - y + _m};\n        return {x, z - y};\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: Numeric/barrett.hpp
  requiredBy:
  - Numeric/DynamicModint.hpp
  - Numeric/Binomial.hpp
  timestamp: '2026-05-29 21:39:52+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/number_theory/sqrt_mod.test.cpp
  - test/1_library_checker/enumerative_combinatorics/binomial_coefficient_prime_mod.test.cpp
  - test/1_library_checker/enumerative_combinatorics/binomial_coefficient.test.cpp
  - test/1_library_checker/linear_algebra/matrix_det_arbitrary_mod.test.cpp
documentation_of: Numeric/barrett.hpp
layout: document
redirect_from:
- /library/Numeric/barrett.hpp
- /library/Numeric/barrett.hpp.html
title: Numeric/barrett.hpp
---
